#
/*

	C compiler-- pass 1 header


*/

/*
  parameters
*/

#define	ncps	8
#define	hshsiz	200
#define	cmsiz	40
#define	swsiz	200
#define	OSSIZ	500
#define	dimsiz	100
#define	NBPW	16
#define	NBPC	8
#define	NCPW	2
#define	STRSIZ	256

/* comment: syntax tree node */
struct tnode {
	/* comment: operator */
	int	op;
	/* comment: value type */
	int	type;
	int	dimp;
	/* comment: left and right operand */
	struct	tnode *tr1, *tr2;
};

struct {
	int	op;
	int	type;
	/* comment: multi-dimensional array */
	char	ssp;		/* subscript list */
	/* comment: also point to dimtab */
	char	lenp;		/* structure length */
};

/* comment: node of a NAME */
struct tname {
	int	op;
	int	type;
	int	dimp;
	int	class;
	int	offset;
	int	nloc;
};

struct txname {
	int	op;
	int	type;
	int	dimp;
	int	class;
	int	offset;
	char	nname[ncps];
};

struct tconst {
	int	op;
	int	type;
	int	dimp;
	int	value;
};

struct hshtab {
	/* comment: storage class */
	char	hclass;
	char	hflag;
	/* comment: type */
	int	htype;
	int	hdimp;
	/* comment: offset to stack base pointer if auto storage class */
	/* comment: register number of register if register storage class */
	/* comment: isn if static storage class */
	int	hoffset;
	char	name[ncps];
};

struct {
	char	hclass;
	char	hflag;
	int	htype;
	char	flen;		/* Field length */
	char	bitoffs;	/* Offset of field */
};

struct swtab {
	int	swlab;
	int	swval;
};

struct	bnode {
	int	bop;
	struct	tnode *btree;
	int	lbl;
	int	cond;
};

char	cvtab[4][4];
/* comment: string buffer */
char	savstr[STRSIZ];
/* comment: string pointer */
char	*strptr;
int	opdope[];
char	ctab[];
/* comment: symbol buffer for lexer symbol() */
char	symbuf[ncps+2];
int	hshused;
struct	hshtab	hshtab[hshsiz];
int	*space;
int	*cp;
int	cmst[cmsiz];
int	isn;
/* comment: switch statement case's label and constant values */
struct	swtab	swtab[swsiz];
/* comment: parsing pointer */
struct	swtab	*swp;
int	contlab;
/* comment: break label */
int	brklab;
int	retlab;
/* comment: switch statement default label */
int	deflab;
int	nauto;
int	autolen;
int	peeksym;
int	peekc;
int	eof;		/* comment: end of file flag, set by symbol() */
int	line;
int	osspace[OSSIZ];
int	*treespace;
/* comment: current defining symbol */
struct	hshtab	*defsym;
struct	hshtab	*funcsym;
/* comment: external definition flag */
int	xdflg;
int	proflg;
int	stflg;
/* comment: current symbol for lookup(), thus symbol() */
struct	hshtab	*csym;
/* comment: current symbol value */
int	cval;
/* comment: crrent float symbol value */
double	fcval;
/* comment: number of chars in a string literal */
int	nchstr;
int	nerror;
struct	hshtab	*paraml;
struct	hshtab	*parame;
int	strflg;
int	mosflg;
/* comment: flag to indicate whether it is parsing a initializer */
int	initflg;
int	inhdr;
/* comment: storage for structure length or rank of array */
int	dimtab[dimsiz];
char	obuf[518];
char	sbuf[518];
int	dimp;
int	regvar;
/* comment: structure bit field offset */
int	bitoffs;
/* comment: function body code block */
struct	tname	funcblk;

/*
 * comment: symbols
 */

/*
  operators
*/
#define	EOF	0
#define	SEMI	1
#define	LBRACE	2
#define	RBRACE	3
#define	LBRACK	4
#define	RBRACK	5
#define	LPARN	6
#define	RPARN	7
#define	COLON	8
#define	COMMA	9
#define	FSEL	10

#define	KEYW	19
#define	NAME	20
#define	CON	21
#define	STRING	22
#define	FCON	23
#define	SFCON	24

#define	SIZEOF	91
#define	INCBEF	30
#define	DECBEF	31
#define	INCAFT	32
#define	DECAFT	33
#define	EXCLA	34
#define	AMPER	35
#define	STAR	36
#define	NEG	37
#define	COMPL	38

#define	DOT	39
#define	PLUS	40
#define	MINUS	41
#define	TIMES	42
#define	DIVIDE	43
#define	MOD	44
#define	RSHIFT	45
#define	LSHIFT	46
#define	AND	47
#define	OR	48
#define	EXOR	49
#define	ARROW	50
#define	ITOF	51
#define	FTOI	52
#define	LOGAND	53
#define	LOGOR	54
#define	FTOL	56
#define	LTOF	57
#define	ITOL	58
#define	LTOI	59

#define	EQUAL	60
#define	NEQUAL	61
#define	LESSEQ	62
#define	LESS	63
#define	GREATEQ	64
#define	GREAT	65
#define	LESSEQP	66
#define	LESSP	67
#define	GREATQP	68
#define	GREATP	69

#define	ASPLUS	70
#define	ASMINUS	71
#define	ASTIMES	72
#define	ASDIV	73
#define	ASMOD	74
#define	ASRSH	75
#define	ASLSH	76
#define	ASSAND	77
#define	ASOR	78
#define	ASXOR	79
#define	ASSIGN	80

#define	QUEST	90
#define	CALL	100
#define	MCALL	101
#define	JUMP	102
#define	CBRANCH	103
#define	INIT	104
#define	SETREG	105
#define	RFORCE	110
#define	BRANCH	111
/* comment: create a label */
#define	LABEL	112
#define	NLABEL	113
#define	RLABEL	114

/*
  types
*/
#define	INT	0
#define	CHAR	1
#define	FLOAT	2
#define	DOUBLE	3
#define	STRUCT	4
#define	RSTRUCT	5
#define	LONG	6
#define	NOTYPE	7	/* used internally */

/* comment: see 8.4 Meaning of declarators in C reference manual */
/* comment: structure of type bit fields 
 * 1..3: basic type
 * 4..5: a pointer to the ...
 *			or a function returning ...
 *          or a array of ...
 * 6..7: the same as 4..5 */
#define	ALIGN	01
#define	TYPE	07
#define	TYLEN	2
/* comment: reference type mask */
#define	XTYPE	(03<<3)
#define	PTR	010
#define	FUNC	020
#define	ARRAY	030

/*
  storage classes
*/
#define	KEYWC	1
#define	MOS	10
#define	AUTO	11
#define	EXTERN	12
#define	STATIC	13
#define	REG	14
#define	STRTAG	15
/* comment: function's argument declarations */
#define ARG	16
/* comment: function's argument names */
#define	ARG1	17
#define	FMOS	18

/*
  keywords
*/
#define	GOTO	20
#define	RETURN	21
#define	IF	22
#define	WHILE	23
#define	ELSE	24
#define	SWITCH	25
#define	CASE	26
#define	BREAK	27
#define	CONTIN	28
#define	DO	29
#define	DEFAULT	30
#define	FOR	31

/*
  characters
*/
#define	INSERT	119
#define	PERIOD	120
#define	SQUOTE	121
#define	DQUOTE	122
#define	LETTER	123
#define	DIGIT	124
#define	NEWLN	125
#define	SPACE	126
#define	UNKN	127

/*
 * Special operators in intermediate code
 */
/* comment: byte data .byte, for char constant and string */
#define	BDATA	200
/* comment: word data .word, for word, float, double */
#define	WDATA	201
/* comment: .text section */
#define	PROG	202
/* comment: .data section */
#define	DATA	203
/* comment: .bss section, for static variable */
#define	BSS	204
/* comment: .comm, create a common name with reserved storage */
#define	CSPACE	205
/* comment: for reserving space, .=.+n */
#define	SSPACE	206
/* comment: define a global symbol */
#define	SYMDEF	207
/* comment: for setup function call frame */
#define	SAVE	208
/* comment: return from function */
#define	RETRN	209
/* comment: .even for alignment */
#define	EVEN	210
#define	PROFIL	212
#define	SWIT	213
#define	EXPR	214
#define	SNAME	215
#define	RNAME	216
#define	ANAME	217
#define	NULL	218

/*
  Flag bits
*/

#define	BINARY	01
#define	LVALUE	02
/* comment: relational operator */
#define	RELAT	04
#define	ASSGOP	010
#define	LWORD	020
#define	RWORD	040
/* comment: commutative */
#define	COMMUTE	0100
#define	RASSOC	0200
#define	LEAF	0400

/*
 * Conversion codes
 */
#define	ITF	1
#define	ITL	2
#define	LTF	3
#define	ITP	4
#define	PTI	5
#define	FTI	6
#define	LTI	7
#define	FTL	8
#define	XX	15

/*
 * symbol table flags
 */
/* comment: external declaration */
#define	FNDEL	01
/* comment: undefined */
#define	FNUND	02
#define	FKEYW	04			/* comment: KEYWORD */
/* comment: structure bit field */
#define	FFIELD	020
