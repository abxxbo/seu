#pragma once

#include <libc/stdint.h>
#include "vesa.h"
#include "graphics.h"

#define PSF_FONT_MAGIC   0x864ab572 // maybe?

typedef struct {
	uint32_t magic;
	uint32_t version;
	uint32_t headersize;
	uint32_t flags;
	uint32_t numglyph;
	uint32_t bytesperglyph;
	uint32_t height;
	uint32_t width;
} PSF_font;

// import the font
extern char _binary_include_video_font_font_psf_start;
extern char _binary_include_video_font_font_psf_end;

uint16_t* unicode;

void psf_init(){
	uint16_t glyph = 0;
	PSF_font* font = (PSF_font*)&_binary_include_video_font_font_psf_start;
	char *s = (char *)((unsigned char*)&_binary_include_video_font_font_psf_start +
    font->headersize + font->numglyph * font->bytesperglyph);
	while(s>_binary_include_video_font_font_psf_end) {
		uint16_t uc = (uint16_t)((unsigned char *)s[0]);
		if(uc == 0xFF) {
				glyph++;
				s++;
				continue;
		} else if(uc & 128) {
				/* UTF-8 to unicode */
				if((uc & 32) == 0 ) {
						uc = ((s[0] & 0x1F)<<6)+(s[1] & 0x3F);
						s++;
				} else
				if((uc & 16) == 0 ) {
						uc = ((((s[0] & 0xF)<<6)+(s[1] & 0x3F))<<6)+(s[2] & 0x3F);
						s+=2;
				} else
				if((uc & 8) == 0) {
						uc = ((((((s[0] & 0x7)<<6)+(s[1] & 0x3F))<<6)+(s[2] & 0x3F))<<6)+(s[3] & 0x3F);
						s+=3;
				} else uc = 0;
		}
		/* save translation */
		unicode[uc] = glyph;
		s++;
  }
}

int scanline = 1024;
#define PIXEL uint32_t

void f_putc(unsigned short int c, int cx, int cy, uint32_t fg, uint32_t bg){
	PSF_font* font = (PSF_font*)&_binary_include_video_font_font_psf_start;
	int bpl = (font->width+7) / 8; // bytes per line
	unsigned char* glyph = (unsigned char*)&_binary_include_video_font_font_psf_start +
													font->headersize + (c > 0 && c < font->numglyph ? c : 0) *
													font->bytesperglyph;
	// upper left corner
	int offs = (cy * font->height * scanline) + (cx * (font->width + 1) * sizeof(PIXEL));
	int x, y, line, mask;
	for(y = 0; y < font->height; y++){
		line = offs;
		mask = 1 << (font->width-1);
		for(x = 0; x < font->width; x++){

			mask >>= 1; // adjust to next pixel
			line += sizeof(PIXEL);
		}
		// adjust to next line
		glyph += bpl;
		offs  += scanline;
	}
}