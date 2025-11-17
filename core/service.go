/*
Service is a layer which is responsible for scraping data,
using dbus, provided by Application class
*/
package core

import (
	"fmt"
	"path/filepath"
	"strings"
	"time"

	dbus "github.com/coreos/go-systemd/v22/dbus"
)

type Service struct {
	*Application
	ch        chan string
	unitFiles []dbus.UnitFile
}

func NewService(a *Application) *Service {
	ch := make(chan string)
	return &Service{Application: a, ch: ch}
}

// Burn this whole fucking code alive and never ever touch it again
func (s *Service) Initialize() {
	go func() {
		for {
			unitFiles, err := s.Connection.ListUnitFilesContext(s.Context)
			if err == nil {
				s.mu.Lock()
				s.unitFiles = unitFiles
				s.mu.Unlock()
				time.Sleep(30 * time.Second)
			}
			time.Sleep(30 * time.Second)
		}
	}()
}

func (s *Service) ListUnits() (units []dbus.UnitStatus, err error) {
	loadedUnits, err := s.Connection.ListUnitsContext(s.Context)
	if err != nil {
		return
	}
	unitMap := make(map[string]dbus.UnitStatus)
	for _, unit := range loadedUnits {
		unitMap[unit.Name] = unit
	}
	for _, unitFile := range s.unitFiles {
		unitName := filepath.Base(unitFile.Path)
		if _, exists := unitMap[unitName]; !exists {
			unitMap[unitName] = dbus.UnitStatus{
				Name:        unitName,
				LoadState:   "unloaded",
				ActiveState: "inactive",
				SubState:    "dead",
			}
		}
	}

	for _, unit := range unitMap {
		if strings.HasSuffix(unit.Name, ".service") {
			units = append(units, unit)
		}
	}

	return
}

func (s *Service) ListAllUnits() (units []dbus.UnitStatus, err error) {
	units, err = s.Connection.ListUnitsContext(s.Context)
	if err != nil {
		return
	}
	return
}

func (s *Service) RestartUnitByName(name string) {
	status, err := s.Connection.RestartUnitContext(s.Context, name, "replace", s.ch)
	if err != nil {
		return
	}
	fmt.Printf("%v\n", status)
}
