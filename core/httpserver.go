package core

import (
	"net/http"
)

type HttpServer struct {
	mux *http.ServeMux
	*Handler
}

func HttpInit(h Handler) *HttpServer {
	mux := http.NewServeMux()
	return &HttpServer{mux: mux, Handler: &h}
}

func (s *HttpServer) GET(relativePath string, handler HandlerFunc) {
	path := http.MethodGet + " " + relativePath
	s.mux.HandleFunc(path, handler)
}

func (s *HttpServer) POST(relativePath string, handler HandlerFunc) {
	path := http.MethodPost + " " + relativePath
	s.mux.HandleFunc(path, handler)
}
