ZIP = LIB_DS4432U+T\&R.zip
URL = https://componentsearchengine.com/part-view/DS4432U%2BT%26R/Analog%20Devices

TMP = tmp
TMP_DIR = $(TMP)/DS4432U+T\&R
TMP_KICAD = $(TMP_DIR)/KiCad
TMP_3D = $(TMP_DIR)/3D

KICAD_MOD_SRC = $(TMP_KICAD)/SOP65P490X110-8N.kicad_mod
KICAD_SYM_SRC = $(TMP_KICAD)/DS4432U+T\&R.kicad_sym
STP_SRC = $(TMP_3D)/DS4432U+T\&R.stp

KICAD_PRETTY = DS4432U+T\&R.pretty
KICAD_MOD = $(KICAD_PRETTY)/SOP65P490X110-8N.kicad_mod
KICAD_SYM = DS4432U+T\&R.kicad_sym
STP = DS4432U+T\&R.stp

SRC = $(KICAD_MOD_SRC) $(KICAD_SYM_SRC) $(STP_SRC)
DEST = $(KICAD_PRETTY) $(KICAD_MOD) $(KICAD_SYM) $(STP)

.PHONY: all clean

all: $(DEST)

clean:
	rm -rf $(TMP) $(DEST)

$(ZIP):
	@if [ ! -f $@ ]; then \
		echo "Download $@ from $(URL)"; \
		exit 1; \
	fi

$(TMP): $(ZIP)
	unzip -o $< -d $@

$(SRC): | $(TMP)
	@if [ ! -f $@ ]; then \
		echo "$@ not found. $(ZIP) may be updated."; \
		exit 1; \
	fi

$(KICAD_PRETTY):
	mkdir $@

$(KICAD_MOD): $(KICAD_MOD_SRC) $(KICAD_PRETTY)
	cp $< $@

$(KICAD_SYM): $(KICAD_SYM_SRC)
	cp $< $@

$(STP): $(STP_SRC)
	cp $< $@
