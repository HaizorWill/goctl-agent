/*
Handler is a layer responsible for processing http requests
*/
package core

import (
	"encoding/json"
	"fmt"
	"net/http"
)

type Handler struct {
	*Service
}

type HandlerFunc func(http.ResponseWriter, *http.Request)

func NewHandler(s *Service) *Handler {
	return &Handler{Service: s}
}

func (h *Handler) Services(w http.ResponseWriter, r *http.Request) {
	units, err := h.ListAllUnits()
	if err != nil {
		//Logging????
		fmt.Print(err)
	}
	jUnits, err := json.MarshalIndent(units, "", "    ")
	if err != nil {
		LogInfo("Failed to... BlahBLAH")
	}
	w.Write(jUnits)
}
