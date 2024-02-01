.PHONY: clean

SVG_CONV := inkscape
OUT_TYPE_FLAG := --export-type=
OUT_NAME_FLAG := --export-filename=

SVG_DIR := ./svg/
PDF_DIR := ./

SVGS := $(wildcard $(SVG_DIR)/*.svg)
PDFS := $(SVGS:$(SVG_DIR)/%.svg=$(PDF_DIR)/%.pdf)

all: svg2pdf

svg2pdf: $(PDFS)

$(PDF_DIR)%.pdf: $(SVG_DIR)%.svg
	$(SVG_CONV) $(OUT_NAME_FLAG)$@ $(OUT_TYPE_FLAG)"pdf" $^

clean:
	rm *.pdf
