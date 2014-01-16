
#ifndef _U_DRAWLIB_H_
#define _U_DRAWLIB_H_

/********************************* Structures ******************************/

typedef struct {
	int r;
	int g;
	int b;
	int a;
} rgb128;

typedef struct {
	int h;
	int s;
	int l;
	int a;
} hsl128;

/*********************************** Macros ********************************/

#define SETRECT(rect, l, t, r, b) (rect).left = (l); (rect).top = (t); (rect).right = (r); (rect).bottom = (b);
#define MOVERECT(r, h, v) (r).left += (h); (r).top += (v); (r).right += (h); (r).bottom += (v);
#define MOVERECTTOZERO(r) (r).right += 0 - (r).left; (r).bottom += 0 - (r).top; (r).left = 0; (r).top = 0; 
#ifndef EXPANDRECT
#define EXPANDRECT(r) (r).left, (r).top, (r).right, (r).bottom
#endif
#define EXPANDRECTLT(r) (r).left, (r).top
#define EXPANDRECTWH(r) (r).left, (r).top, (r).right - (r).left, (r).bottom - (r).top
#define RECTW(r) ((r).right - (r).left)
#define RECTH(r) ((r).bottom - (r).top)
#define SCALERECT(r, h, v) (r).left -= (h); (r).top -= (v); (r).right += (h); (r).bottom += (v);
#define RESIZERECT(rect, l, t, r, b) (rect).left += (l); (rect).top += (t); (rect).right += (r); (rect).bottom += (b);
#define RECTCENTER(p, r) (p).x = ((r).left + (r).right)/2; (p).y = ((r).top + (r).bottom)/2;
#define RECTTOSIZE(s, r) (s).right = (r).right - (r).left; (s).bottom = (r).bottom - (r).top; (s).left = 0; (s).top = 0;

#define SETBOUNDS(v, nmin, nmax)	\
	if ((nmax - nmin) < 0) {	\
		if (v < nmax) {				\
			v = nmax;				\
		}							\
		else if (v > nmin){			\
			v = nmin;				\
		}							\
	}								\
	else {							\
		if (v > nmax) {				\
			v = nmax;				\
		}							\
		else if (v < nmin){			\
			v = nmin;				\
		}							\
	}
// end of SETBOUNDS

#define WRAPBOUNDS(v, nmin, nmax)	\
	if ((nmax - nmin) < 0) {	\
		if (v < nmax) {				\
			v = v + (nmax - nmin);	\
		}							\
		else if (v >= nmin) {						\
			v = v - (nmax - nmin);	\
		}							\
	}								\
	else {							\
		if (v > nmax) {				\
			v = v - (nmax - nmin);	\
		}							\
		else if (v <= nmin) {						\
			v = v + (nmax - nmin);	\
		}							\
	}
// end of WRAPBOUNDS

/********************************* Functions *******************************/

#define BLEND_COPY		0
#define BLEND_MULTIPLY	1
#define BLEND_SCREEN	2
#define BLEND_OVERLAY	3

void kxuApplyTexture(HBITMAP hDstBitmap, LPRECT pDstRect, HBITMAP hTexture,
		int xTxOrigin, int yTxOrigin, DWORD Reserved, DWORD Depth = 128);
void kxuBlend(HBITMAP hDstBitmap, LPRECT pDstRect, HBITMAP hSrcBitmap,
		int xSrc, int ySrc, DWORD dwMode, DWORD Depth = 128);
void kxuBlendDC(HBITMAP hDstBitmap, LPRECT pDstRect, HDC hSrcDC,
		int xSrc, int ySrc, DWORD dwMode, DWORD Depth = 128);

void kxuBitBlt(HDC hDstDC, int x, int y, int nWidth, int nHeight, HDC hSrcDC,
		int xSrc, int ySrc, int nWidthSrc, int nHeightSrc, DWORD dwRop);

//.............................................................................

#define GRD_FILL_FIGURE_MASK	0xFF00
#define GRD_FILL_RECT_H			0x0000
#define GRD_FILL_RECT_V			0x0100
#define GRD_FILL_RECT_D			0x0200 // diagonal, fixme - not yet
#define GRD_FILL_CIRCLE			0x0300
#define GRD_FILL_ELLIPSE		0x0400

#define CURVE_MASK				0xFF0000
#define CURVE_LINEAR			0x000000 //	/
#define CURVE_MOREIN			0x010000 //  _|  _
#define CURVE_MOREOUT			0x020000 //     |  _
#define CURVE_MOREEDGE			0x030000 //      _/ 
#define CURVE_LESSEDGE			0x040000 //         _/
										 //        /

#define CURVE_MOREIN2			0x050000 //  _|  _  fixme not yet
#define CURVE_MOREOUT2			0x060000 //     |	fixme not yet


void kxuGradientFill(CDC* pDstDC, LPRECT pDstRect, DWORD dwMode, COLORREF* pColor, LONG* pPoint);
void _kxuGrdFill_Ellipse(CDC* pDstDC, LPRECT pDstRect, DWORD dwMode, COLORREF* pColor, LPPOINT pPoint);
void _kxuGrdFill_Rect(CDC* pDstDC, LPRECT pDstRect, DWORD dwMode, COLORREF* pColor, LONG* pPoint);

void kxuCorrectMinRect(LPRECT r, LPRECT minr, int options = 0);
void kxuCenterRectToAnotherOne(LPRECT r, LPRECT cont);

int kxuGetBitmapSize(HBITMAP bitmap, LPRECT rect);

//.............................................................................
// uDibBitsRGB

class uDibBitsRGB
{
public:
	uDibBitsRGB(HBITMAP hBitmap);
	virtual ~uDibBitsRGB();

public:
	void CancelSave() {changed = 0;};
	int Width() {return bm.bmWidth;};
	int Height() {return bm.bmHeight;};
	COLORREF Get(int x, int y) {return pBits[((bm.bmHeight - y - 1) * bm.bmWidth) + x];};
	COLORREF Get(int p) {return pBits[p];};
	void Set(int x, int y, COLORREF c) {pBits[((bm.bmHeight - y - 1) * bm.bmWidth) + x] = c;};
	void Set(int p, COLORREF c) {pBits[p] = c;};

private:
	int		changed;
	HBITMAP hbitmap;
	HDC		ScreenDC;
	BITMAP	bm;
	BITMAPV4HEADER	bhdr;
	COLORREF*		pBits;
};

//.............................................................................
// uRGBBits
/*
#define UBF_WRAP	1
#define UBF_CANCEL	8

class uRGBBits
{
public:
	uRGBBits(HBITMAP _hbitmap, LPRECT _rect = NULL, int _flags = 0, LPPOINT _origin = NULL);
	virtual ~uRGBBits();

	COLORREF* p;

	void reset();
	void cancel() {flags |= UBF_CANCEL;};

private:
	int		flags;
	int		wrap;
	RECT	rect;
	POINT	origin;
	int	x;
	int	y;

	HBITMAP hbitmap;
	HDC		ScreenDC;
	BITMAP	bm;
	BITMAPV4HEADER	bhdr;
	COLORREF*		pBits;
};
*/

//.............................................................................
/* Ternary Raster Codes Table */
/*
const int TROP[] = {
	0x00000042,
	0x00010289,
	0x00020C89,
	0x000300AA,
	0x00040C88,
	0x000500A9,
	0x00060865,
	0x000702C5,
	0x00080F08,
	0x00090245,
	0x000A0329,
	0x000B0B2A,
	0x000C0324,
	0x000D0B25,
	0x000E08A5,
	0x000F0001,
	0x00100C85,
	0x001100A6,
	0x00120868,
	0x001302C8,
	0x00140869,
	0x001502C9,
	0x00165CCA,
	0x00171D54,
	0x00180D59,
	0x00191CC8,
	0x001A06C5,
	0x001B0768,
	0x001C06CA,
	0x001D0766,
	0x001E01A5,
	0x001F0385,
	0x00200F09,
	0x00210248,
	0x00220326,
	0x00230B24,
	0x00240D55,
	0x00251CC5,
	0x002606C8,
	0x00271868,
	0x00280369,
	0x002916CA,
	0x002A0CC9,
	0x002B1D58,
	0x002C0784,
	0x002D060A,
	0x002E064A,
	0x002F0E2A,
	0x0030032A,
	0x00310B28,
	0x00320688,
	0x00330008,
	0x003406C4,
	0x00351864,
	0x003601A8,
	0x00370388,
	0x0038078A,
	0x00390604,
	0x003A0644,
	0x003B0E24,
	0x003C004A,
	0x003D18A4,
	0x003E1B24,
	0x003F00EA,
	0x00400F0A,
	0x00410249,
	0x00420D5D,
	0x00431CC4,
	0x00440328,
	0x00450B29,
	0x004606C6,
	0x0047076A,
	0x00480368,
	0x004916C5,
	0x004A0789,
	0x004B0605,
	0x004C0CC8,
	0x004D1954,
	0x004E0645,
	0x004F0E25,
	0x00500325,
	0x00510B26,
	0x005206C9,
	0x00530764,
	0x005408A9,
	0x00550009,
	0x005601A9,
	0x00570389,
	0x00580785,
	0x00590609,
	0x005A0049,
	0x005B18A9,
	0x005C0649,
	0x005D0E29,
	0x005E1B29,
	0x005F00E9,
	0x00600365,
	0x006116C6,
	0x00620786,
	0x00630608,
	0x00640788,
	0x00650606,
	0x00660046,
	0x006718A8,
	0x006858A6,
	0x00690145,
	0x006A01E9,
	0x006B178A,
	0x006C01E8,
	0x006D1785,
	0x006E1E28,
	0x006F0C65,
	0x00700CC5,
	0x00711D5C,
	0x00720648,
	0x00730E28,
	0x00740646,
	0x00750E26,
	0x00761B28,
	0x007700E6,
	0x007801E5,
	0x00791786,
	0x007A1E29,
	0x007B0C68,
	0x007C1E24,
	0x007D0C69,
	0x007E0955,
	0x007F03C9,
	0x008003E9,
	0x00810975,
	0x00820C49,
	0x00831E04,
	0x00840C48,
	0x00851E05,
	0x008617A6,
	0x008701C5,
	0x008800C6,
	0x00891B08,
	0x008A0E06,
	0x008B0666,
	0x008C0E08,
	0x008D0668,
	0x008E1D7C,
	0x008F0CE5,
	0x00900C45,
	0x00911E08,
	0x009217A9,
	0x009301C4,
	0x009417AA,
	0x009501C9,
	0x00960169,
	0x0097588A,
	0x00981888,
	0x00990066,
	0x009A0709,
	0x009B07A8,
	0x009C0704,
	0x009D07A6,
	0x009E16E6,
	0x009F0345,
	0x00A000C9,
	0x00A11B05,
	0x00A20E09,
	0x00A30669,
	0x00A41885,
	0x00A50065,
	0x00A60706,
	0x00A707A5,
	0x00A803A9,
	0x00A90189,
	0x00AA0029,
	0x00AB0889,
	0x00AC0744,
	0x00AD06E9,
	0x00AE0B06,
	0x00AF0229,
	0x00B00E05,
	0x00B10665,
	0x00B21974,
	0x00B30CE8,
	0x00B4070A,
	0x00B507A9,
	0x00B616E9,
	0x00B70348,
	0x00B8074A,
	0x00B906E6,
	0x00BA0B09,
	0x00BB0226,
	0x00BC1CE4,
	0x00BD0D7D,
	0x00BE0269,
	0x00BF08C9,
	0x00C000CA,
	0x00C11B04,
	0x00C21884,
	0x00C3006A,
	0x00C40E04,
	0x00C50664,
	0x00C60708,
	0x00C707AA,
	0x00C803A8,
	0x00C90184,
	0x00CA0749,
	0x00CB06E4,
	0x00CC0020,
	0x00CD0888,
	0x00CE0B08,
	0x00CF0224,
	0x00D00E0A,
	0x00D1066A,
	0x00D20705,
	0x00D307A4,
	0x00D41D78,
	0x00D50CE9,
	0x00D616EA,
	0x00D70349,
	0x00D80745,
	0x00D906E8,
	0x00DA1CE9,
	0x00DB0D75,
	0x00DC0B04,
	0x00DD0228,
	0x00DE0268,
	0x00DF08C8,
	0x00E003A5,
	0x00E10185,
	0x00E20746,
	0x00E306EA,
	0x00E40748,
	0x00E506E5,
	0x00E61CE8,
	0x00E70D79,
	0x00E81D74,
	0x00E95CE6,
	0x00EA02E9,
	0x00EB0849,
	0x00EC02E8,
	0x00ED0848,
	0x00EE0086,
	0x00EF0A08,
	0x00F00021,
	0x00F10885,
	0x00F20B05,
	0x00F3022A,
	0x00F40B0A,
	0x00F50225,
	0x00F60265,
	0x00F708C5,
	0x00F802E5,
	0x00F90845,
	0x00FA0089,
	0x00FB0A09,
	0x00FC008A,
	0x00FD0A0A,
	0x00FE02A9,
	0x00FF0062,
}; */

#endif // _U_DRAWLIB_H_


