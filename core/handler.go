/*
Handler is a layer responsible for processing http requests
*/
package core

import (
	"encoding/json"
	"fmt"
	"log"
	"net/http"
	"time"
)

type Handler struct {
	*Service
}

type HandlerFunc func(http.ResponseWriter, *http.Request)

func NewHandler(s *Service) *Handler {
	return &Handler{Service: s}
}

func (h *Handler) Services(w http.ResponseWriter, r *http.Request) {
	start := time.Now()
	units, err := h.ListUnits()
	if err != nil {
		//Logging????
		fmt.Print(err)
	}
	jUnits, err := json.MarshalIndent(units, "", "    ")
	if err != nil {
		LogInfo("Failed to... BlahBLAH")
	}
	w.Write(jUnits)
	log.Printf("Request took: %s", time.Since(start))
}
