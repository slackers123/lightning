/*
 * Copyright (C) 2012  Free Software Foundation, Inc.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * Authors:
 *	Paulo Cesar Pereira de Andrade
 */

#if PROTO
/* quite a lot of space for fixed computation of possible stack arguments
 * this currently is done mostly to keep it simple, as the vm has only
 * one function */
#  define stack_framesize		224
#  define ii(i)				*_jit->pc.ui++ = i
#  define can_sign_extend_short_p(im)	((im) >= -32768 && (im) <= 32767)
#  define can_zero_extend_short_p(im)	((im) >= 0 && (im) <= 65535)
#  define can_sign_extend_jump_p(im)	((im) >= -33554432 && (im) <= 33554431)
#  define _R0_REGNO			0
#  define _SP_REGNO			1
#  define _FP_REGNO			31
#  define ldxi(r0,r1,i0)		ldxi_i(r0,r1,i0)
#  define stxi(i0,r0,r1)		stxi_i(i0,r0,r1)
#  define FXO(o,d,a,b,e,x)		_FXO(_jit,o,d,a,b,e,x,0)
#  define FXO_(o,d,a,b,e,x)		_FXO(_jit,o,d,a,b,e,x,1)
static void _FXO(jit_state_t*,int,int,int,int,int,int,int);
#  define FDs(o,d,a,s)			_FDs(_jit,o,d,a,s)
static void _FDs(jit_state_t*,int,int,int,int);
#  define FDu(o,d,a,s)			_FDu(_jit,o,d,a,s)
static void _FDu(jit_state_t*,int,int,int,int);
#  define FX(o,d,a,b,x)			_FX(_jit,o,d,a,b,x,0)
#  define FX_(o,d,a,b,x)		_FX_(_jit,o,d,a,b,x,1)
static void _FX(jit_state_t*,int,int,int,int,int,int);
#  define FI(o,t,a,k)			_FI(_jit,o,t,a,k)
static void _FI(jit_state_t*,int,int,int,int);
#  define FB(o,bo,bi,t,a,k)		_FB(_jit,o,bo,bi,t,a,k)
static void _FB(jit_state_t*,int,int,int,int,int,int);
#  define FXL(o,bo,bi,x)		_FXL(_jit,o,bo,bi,x,0)
#  define FXL_(o,bo,bi,x)		_FXL(_jit,o,bo,bi,x,1)
static void _FXL(jit_state_t*,int,int,int,int,int);
#  define FC(o,d,l,a,b,x)		_FC(_jit,o,d,l,a,b,x)
static void _FC(jit_state_t*,int,int,int,int,int,int);
#  define FCI(o,d,l,a,s)		_FCI(_jit,o,d,l,a,s)
static void _FCI(jit_state_t*,int,int,int,int,int);
#  define FXFX(o,s,x,f)			_FXFX(_jit,o,s,x,f)
static void _FXFX(jit_state_t*,int,int,int,int);
#  define FM(o,s,a,h,b,e,r)		_FM(_jit,o,s,a,h,b,e,r)
static void _FM(jit_state_t*,int,int,int,int,int,int,int);
#  define CR_0				0
#  define CR_1				1
#  define CR_2				2
#  define CR_3				3
#  define CR_4				4
#  define CR_5				5
#  define CR_6				6
#  define CR_7				7
#  define CR_LT				0
#  define CR_GT				1
#  define CR_EQ				2
#  define CR_SO				3
#  define CR_UN				3
#  define BCC_F				4
#  define BCC_T				12
#  define ADD(d,a,b)			FXO(31,d,a,b,0,266)
#  define ADD_(d,a,b)			FXO_(31,d,a,b,0,266)
#  define ADDO(d,a,b)			FXO(31,d,a,b,1,266)
#  define ADDO_(d,a,b)			FXO_(31,d,a,b,1,266)
#  define ADDC(d,a,b)			FXO_(31,d,a,b,0,10)
#  define ADDC_(d,a,b)			FXO_(31,d,a,b,0,10)
#  define ADDCO(d,a,b)			FXO(31,d,a,b,1,10)
#  define ADDCO_(d,a,b)			FXO_(31,d,a,b,1,10)
#  define ADDE(d,a,b)			FXO(31,d,a,b,0,138)
#  define ADDE_(d,a,b)			FXO_(31,d,a,b,0,138)
#  define ADDEO(d,a,b)			FXO(31,d,a,b,1,138)
#  define ADDEO_(d,a,b)			FXO_(31,d,a,b,1,138)
#  define ADDI(d,a,s)			FDs(14,d,a,s)
#  define ADDIC(d,a,s)			FDs(12,d,a,s)
#  define ADDIC_(d,a,s)			FDs(13,d,a,s)
#  define ADDIS(d,a,s)			FDs(15,d,a,s)
#  define LIS(d,s)			ADDIS(d,0,s)
#  define ADDME(d,a)			FXO(31,d,a,0,0,234)
#  define ADDME_(d,a)			FXO_(31,d,a,0,0,234)
#  define ADDMEO(d,a)			FXO(31,d,a,0,1,234)
#  define ADDMEO_(d,a)			FXO_(31,d,a,0,1,234)
#  define ADDZE(d,a)			FXO(31,d,a,0,0,202)
#  define ADDZE_(d,a)			FXO_(31,d,a,0,0,202)
#  define ADDZEO(d,a)			FXO(31,d,a,0,1,202)
#  define ADDZEO_(d,a)			FXO_(31,d,a,0,1,202)
#  define AND(d,a,b)			FX(31,a,d,b,28)
#  define ANDC(d,a,b)			FXO(31,a,d,b,0,60)
#  define ANDC_(d,a,b)			FXO_(31,a,d,b,0,60)
#  define AND_(d,a,b)			FX_(31,a,b,d,28)
#  define ANDI_(d,a,u)			FDu(28,a,d,u)
#  define ANDIS_(d,a,u)			FDu(29,a,d,u)
#  define B(t)				FI(18,t,0,0)
#  define BA(t)				FI(18,t,1,0)
#  define BL(t)				FI(18,t,0,1)
#  define BLA(t)			FI(18,t,1,1)
#  define BC(o,i,t)			FB(16,o,i,t,0,0)
#  define BCA(o,i,t)			FB(16,o,i,t,1,0)
#  define BCL(o,i,t)			FB(16,o,i,t,0,1)
#  define BCLA(o,i,t)			FB(16,o,i,t,1,1)
#  define BLT(t)			BC(BCC_T,CR_LT,t)
#  define BLE(t)			BC(BCC_F,CR_GT,t)
#  define BEQ(t)			BC(BCC_T,CR_EQ,t)
#  define BGE(t)			BC(BCC_F,CR_LT,t)
#  define BGT(t)			BC(BCC_T,CR_GT,t)
#  define BNE(t)			BC(BCC_F,CR_EQ,t)
#  define BUN(t)			BC(BCC_T,CR_UN,t)
#  define BNU(t)			BC(BCC_F,CR_UN,t)
#  define BCCTR(o,i)			FXL(19,o,i,528)
#  define BCCTRL(o,i)			FXL_(19,o,i,528)
#  define BLTCTR()			BCCTR(BCC_T,CR_LT)
#  define BLECTR()			BCCTR(BCC_F,CR_GT)
#  define BEQCTR()			BCCTR(BCC_T,CR_EQ)
#  define BGECTR()			BCCTR(BCC_F,CR_LT)
#  define BGTCTR()			BCCTR(BCC_T,CR_GT)
#  define BNECTR()			BCCTR(BCC_F,CR_EQ)
#  define BCTR()			BCCTR(20,0)
#  define BCTRL()			BCCTRL(20,0)
#  define BCLR(o,i)			FXL(19,o,i,16)
#  define BCLRL(o,i)			FXL_(19,o,i,16)
#  define BLTLR()			BCLR(BCC_T,CR_LT)
#  define BLELR()			BCLR(BCC_F,CR_GT)
#  define BEQLR()			BCLR(BCC_T,CR_EQ)
#  define BGELR()			BCLR(BCC_F,CR_LT)
#  define BGTLR()			BCLR(BCC_T,CR_GT)
#  define BNELR()			BCLR(BCC_F,CR_EQ)
#  define BLR()				BCLR(20,0)
#  define BLRL()			BCLRL(20,0)
#  define XCMP(cr,l,a,b)		FC(31,cr,l,a,b,0)
#  define CMPD(a,b)			XCMP(0,1,a,b)
#  define CMPW(a,b)			XCMP(0,0,a,b)
#  define XCMPI(cr,l,a,s)		FCI(11,cr,l,a,s)
#  define CMPDI(a,s)			XCMPI(0,1,a,s)
#  define CMPWI(a,s)			XCMPI(0,0,a,s)
#  define XCMPL(cr,l,a,b)		FC(31,cr,l,a,b,32)
#  define CMPLD(a,b)			XCMPL(0,1,a,b)
#  define CMPLW(a,b)			XCMPL(0,0,a,b)
#  define XCMPLI(cr,l,a,u)		FCI(10,cr,l,a,u)
#  define CMPLDI(a,s)			XCMPLI(0,1,a,s)
#  define CMPLWI(a,s)			XCMPLI(0,0,a,s)
#  define CNTLZW(a,s)			FX(31,s,a,0,26)
#  define CNTLZW_(a,s)			FX_(31,s,a,0,26)
#  define CRAND(d,a,b)			FX(19,d,a,b,257)
#  define CRANDC(d,a,b)			FX(19,d,a,b,129)
#  define CREQV(d,a,b)			FX(19,d,a,b,289)
#  define CRSET(d)			CREQV(d,d,d)
#  define CRNAND(d,a,b)			FX(19,d,a,b,225)
#  define CRNOR(d,a,b)			FX(19,d,a,b,33)
#  define CRNOT(d,a)			CRNOR(d,a,a)
#  define CROR(d,a,b)			FX(19,d,a,b,449)
#  define CRMOVE(d,a)			CROR(d,a,a)
#  define CRORC(d,a,b)			FX(19,d,a,b,417)
#  define CRXOR(d,a,b)			FX(19,d,a,b,193)
#  define CRCLR(d)			CRXOR(d,d,d)
#  define DCBA(a,b)			FX(31,0,a,b,758)
#  define DCBF(a,b)			FX(31,0,a,b,86)
#  define DCBI(a,b)			FX(31,0,a,b,470)
#  define DCBST(a,b)			FX(31,0,a,b,54)
#  define DCBT(a,b)			FX(31,0,a,b,278)
#  define DCBTST(a,b)			FX(31,0,a,b,246)
#  define DCBZ(a,b)			FX(31,0,a,b,1014)
#  define DIVW(d,a,b)			FXO(31,d,a,b,0,491)
#  define DIVW_(d,a,b)			FXO_(31,d,a,b,0,491)
#  define DIVWO(d,a,b)			FXO(31,d,a,b,1,491)
#  define DIVWO_(d,a,b)			FXO_(31,d,a,b,1,491)
#  define DIVWU(d,a,b)			FXO(31,d,a,b,0,459)
#  define DIVWU_(d,a,b)			FXO_(31,d,a,b,0,459)
#  define DIVWUO(d,a,b)			FXO(31,d,a,b,1,459)
#  define DIVWUO_(d,a,b)		FXO_(31,d,a,b,1,459)
#  define ECIWX(d,a,b)			FX(31,d,a,b,310)
#  define ECOWX(s,a,b)			FX(31,s,a,b,438)
#  define EIEIO()			FX(31,0,0,0,854)
#  define EQV(d,a,b)			FX(31,a,d,b,284)
#  define EQV_(d,a,b)			FX_(31,a,d,b,284)
#  define EXTSB(d,a)			FX(31,a,d,0,954)
#  define EXTSB_(d,a)			FX_(31,a,d,0,954)
#  define EXTSH(d,a)			FX(31,a,d,0,922)
#  define EXTSH_(d,a)			FX_(31,a,d,0,922)
#  define ICIB(a,b)			FX(31,0,a,b,982)
#  define ISYNC()			FXL(19,0,0,150)
#  define LBZ(d,a,s)			FDs(34,d,a,s)
#  define LBZU(d,a,s)			FDs(35,d,a,s)
#  define LBZUX(d,a,b)			FX(31,d,a,b,119)
#  define LBZX(d,a,b)			FX(31,d,a,b,87)
#  define LHA(d,a,s)			FDs(42,d,a,s)
#  define LHAU(d,a,s)			FDs(43,d,a,s)
#  define LHAUX(d,a,b)			FX(31,d,a,b,375)
#  define LHAX(d,a,b)			FX(31,d,a,b,343)
#  define LHRBX(d,a,b)			FX(31,d,a,b,790)
#  define LHZ(d,a,s)			FDs(40,d,a,s)
#  define LHZU(d,a,s)			FDs(41,d,a,s)
#  define LHZUX(d,a,b)			FX(31,d,a,b,311)
#  define LHZX(d,a,b)			FX(31,d,a,b,279)
#  define LA(d,a,s)			ADDI(d,a,s)
#  define LI(d,s)			ADDI(d,0,s)
#  define LMW(d,a,s)			FDs(46,d,a,s)
#  define LSWI(d,a,n)			FX(31,d,a,n,597)
#  define LSWX(d,a,b)			FX(31,d,a,b,533)
#  define LWARX(d,a,b)			FX(31,d,a,b,20)
#  define LWBRX(d,a,b)			FX(31,d,a,b,534)
#  define LWZ(d,a,s)			FDs(32,d,a,s)
#  define LWZU(d,a,s)			FDs(33,d,a,s)
#  define LWZUX(d,a,b)			FX(31,d,a,b,55)
#  define LWZX(d,a,b)			FX(31,d,a,b,23)
#  define MCRF(d,s)			FXL(19,d<<2,(s)<<2,0)
#  define MCRXR(d)			FX(31,d<<2,0,0,512)
#  define MFCR(d)			FX(31,d,0,0,19)
#  define MFMSR(d)			FX(31,d,0,0,83)
#  define MFSPR(d,s)			FXFX(31,d,s<<5,339)
#  define MFXER(d)			MFSPR(d,1)
#  define MFLR(d)			MFSPR(d,8)
#  define MFCTR(d)			MFSPR(d,9)
#  define MFSR(d,s)			FX(31,d,s,0,595)
#  define MFSRIN(d,b)			FX(31,d,0,b,659)
#  define MFTB(d,x,y)			FXFX(31,d,(x)|((y)<<5),371)
#  define MFTBL(d)			MFTB(d,8,12)
#  define MFTBU(d)			MFTB(d,8,13)
#  define MTCRF(c,s)			FXFX(31,s,c<<1,144)
#  define MTCR(s)			MTCRF(0xff,s)
#  define MTMSR(s)			FX(31,s,0,0,146)
#  define MTSPR(d,s)			FXFX(31,d,s<<5,467)
#  define MTXER(d)			MTSPR(d,1)
#  define MTLR(d)			MTSPR(d,8)
#  define MTCTR(d)			MTSPR(d,9)
#  define MTSR(r,s)			FX(31,s<<1,r,0,210)
#  define MTSRIN(r,b)			FX(31,r<<1,0,b,242)
#  define MULHW(d,a,b)			FXO(31,d,a,b,0,75)
#  define MULHW_(d,a,b)			FXO_(31,d,a,b,0,75)
#  define MULHWU(d,a,b)			FXO(31,d,a,b,0,11)
#  define MULHWU_(d,a,b)		FXO_(31,d,a,b,0,11)
#  define MULLI(d,a,s)			FDs(07,d,a,s)
#  define MULLW(d,a,b)			FXO(31,d,a,b,0,235)
#  define MULLW_(d,a,b)			FXO_(31,d,a,b,0,235)
#  define MULLWO(d,a,b)			FXO(31,d,a,b,1,235)
#  define MULLWO_(d,a,b)		FXO_(31,d,a,b,1,235)
#  define NAND(d,a,b)			FX(31,a,d,b,476)
#  define NAND_(d,a,b)			FX_(31,a,d,b,476)
#  define NEG(d,a)			FXO(31,d,a,0,0,104)
#  define NEG_(d,a)			FXO_(31,d,a,0,0,104)
#  define NEGO(d,a)			FXO(31,d,a,0,1,104)
#  define NEGO_(d,a)			FXO_(31,d,a,0,1,104)
#  define NOR(d,a,b)			FX(31,a,d,b,124)
#  define NOR_(d,a,b)			FX_(31,a,d,b,124)
#  define NOT(d,s)			NOR(d,s,s)
#  define OR(d,a,b)			FX(31,a,d,b,444)
#  define OR_(d,a,b)			FX_(31,a,d,b,444)
#  define MR(d,a)			OR(d,a,a)
#  define ORC(d,a,b)			FX(31,a,d,b,412)
#  define ORC_(d,a,b)			FX_(31,a,d,b,412)
#  define ORI(d,a,u)			FDu(24,a,d,u)
#  define NOP()				ORI(0,0,0)
#  define ORIS(d,a,u)			FDu(25,a,d,u)
#  define RFI()				FXL(19,0,0,50)
#  define RLWIMI(d,s,h,b,e)		FM(20,s,a,h,b,e,0)
#  define RLWIMI_(d,s,h,b,e)		FM(20,s,a,h,b,e,1)
#  define INSLWI(a,s,n,b)		RLWIMI(a,s,32-b,b,b+n-1)
#  define INSRWI(a,s,n,b)		RLWIMI(a,s,32-(b+n),b,(b+n)-1)
#  define RLWINM(a,s,h,b,e)		FM(21,s,a,h,b,e,0)
#  define RLWINM_(a,s,h,b,e)		FM(21,s,a,h,b,e,1)
#  define EXTLWI(a,s,n,b)		RLWINM(a,s,b,0,n-1)
#  define EXTRWI(a,s,n,b)		RLWINM(a,s,b+n,32-n,31)
#  define ROTLWI(a,s,n)			RLWINM(a,s,n,0,31)
#  define ROTRWI(a,s,n)			RLWINM(a,s,32-n,0,31)
#  define SLWI(a,s,n)			RLWINM(a,s,n,0,31-n)
#  define SRWI(a,s,n)			RLWINM(a,s,32-n,n,31)
#  define CLRLWI(a,s,n)			RLWINM(a,s,0,n,31)
#  define CLRRWI(a,s,n)			RLWINM(a,s,0,0,31-n)
#  define CLRLSWI(a,s,b,n)		RLWINM(a,s,n,b-n,31-n)
#  define RLWNM(a,s,b,m,e)		FM(23,s,a,b,m,e,0)
#  define RLWNM_(a,s,b,m,e)		FM(23,s,a,b,m,e,1)
#  define ROTLW(a,s,b)			RLWNM(a,s,b,0,31)
#  define SC()				FDu(17,0,0,2)
#  define SLW(a,s,b)			FX(31,s,a,b,24)
#  define SLW_(a,s,b)			FX_(31,s,a,b,24)
#  define SRAW(a,s,b)			FX(31,s,a,b,792)
#  define SRAW_(a,s,b)			FX_(31,s,a,b,792)
#  define SRAWI(a,s,h)			FX(31,s,a,h,824)
#  define SRAWI_(a,s,h)			FX_(31,s,a,h,824)
#  define SRW(a,s,b)			FX(31,s,a,b,536)
#  define SRW_(a,s,b)			FX_(31,s,a,b,536)
#  define STB(s,a,d)			FDs(38,s,a,d)
#  define STBU(s,a,d)			FDs(39,s,a,d)
#  define STBUX(s,a,b)			FX(31,s,a,b,247)
#  define STBX(s,a,b)			FX(31,s,a,b,215)
#  define STH(s,a,d)			FDs(44,s,a,d)
#  define STHBRX(s,a,b)			FX(31,s,a,b,918)
#  define STHU(s,a,d)			FDs(45,s,a,d)
#  define STHUX(s,a,b)			FX(31,s,a,b,439)
#  define STHX(s,a,b)			FX(31,s,a,b,407)
#  define STMW(s,a,d)			FDs(47,s,a,d)
#  define STWSI(s,a,nb)			FX(31,s,a,nb,725)
#  define STSWX(s,a,b)			FX(31,s,a,b,661)
#  define STW(s,a,d)			FDs(36,s,a,d)
#  define STWBRX(s,a,b)			FX(31,s,a,b,662)
#  define STWCX_(s,a,b)			FX_(31,s,a,b,150)
#  define STWU(s,a,d)			FDs(37,s,a,d)
#  define STWUX(s,a,b)			FX(31,s,a,b,183)
#  define STWX(s,a,b)			FX(31,s,a,b,151)
#  define SUBF(d,a,b)			FXO(31,d,a,b,0,40)
#  define SUBF_(d,a,b)			FXO_(31,d,a,b,0,40)
#  define SUBFO(d,a,b)			FXO(31,d,a,b,1,40)
#  define SUBFO_(d,a,b)			FXO_(31,d,a,b,1,40)
#  define SUB(d,a,b)			SUBF(d,b,a)
#  define SUB_(d,a,b)			SUBF_(d,b,a)
#  define SUBO(d,a,b)			SUBFO(d,b,a)
#  define SUBO_(d,a,b)			SUBFO_(d,b,a)
#  define SUBI(d,a,s)			ADDI(d,a,-s)
#  define SUBIS(d,a,s)			ADDIS(d,a,-s)
#  define SUBFC(d,a,b)			FXO(31,d,a,b,0,8)
#  define SUBFC_(d,a,b)			FXO_(31,d,a,b,0,8)
#  define SUBFCO(d,a,b)			FXO(31,d,a,b,1,8)
#  define SUBFCO_(d,a,b)		FXO_(31,d,a,b,1,8)
#  define SUBC(d,a,b)			SUBFC(d,b,a)
#  define SUBIC(d,a,s)			ADDIC(d,a,-s)
#  define SUBIC_(d,a,s)			ADDIC_(d,a,-s)
#  define SUBFE(d,a,b)			FXO(31,d,a,b,0,136)
#  define SUBFE_(d,a,b)			FXO_(31,d,a,b,0,136)
#  define SUBFEO(d,a,b)			FXO(31,d,a,b,1,136)
#  define SUBFEO_(d,a,b)		FXO_(31,d,a,b,1,136)
#  define SUBE(d,a,b)			SUBFE(d,b,a)
#  define SUBFIC(d,a,s)			FDs(8,d,a,s)
#  define SUBFME(d,a)			FXO(31,d,a,0,0,232)
#  define SUBFME_(d,a)			FXO_(31,d,a,0,0,232)
#  define SUBFMEO(d,a)			FXO(31,d,a,0,1,232)
#  define SUBFMEO_(d,a)			FXO_(31,d,a,0,1,232)
#  define SUBFZE(d,a)			FXO(31,d,a,0,0,200)
#  define SUBFZE_(d,a)			FXO_(31,d,a,0,0,200)
#  define SUBFZEO(d,a)			FXO(31,d,a,0,1,200)
#  define SUBFZEO_(d,a)			FXO_(31,d,a,0,1,200)
#  define SYNC()			FX(31,0,0,0,598)
#  define TLBIA()			FX(31,0,0,0,370)
#  define TLBIE(b)			FX(31,0,0,b,306)
#  define TLBSYNC()			FX(31,0,0,0,566)
#  define TW(t,a,b)			FX(31,t,a,b,4)
#  define TWEQ(a,b)			FX(31,4,a,b,4)
#  define TWLGE(a,b)			FX(31,5,a,b,4)
#  define TRAP()			FX(31,31,0,0,4)
#  define TWI(t,a,s)			FDs(3,t,a,s)
#  define TWGTI(a,s)			TWI(8,a,s)
#  define TWLLEI(a,s)			TWI(6,a,s)
#  define XOR(d,a,b)			FXO(31,a,d,b,0,316)
#  define XOR_(d,a,b)			FXO_(31,a,d,b,0,316)
#  define XORI(s,a,u)			FDu(26,s,a,u)
#  define XORIS(s,a,u)			FDu(27,s,a,u)
#  define movr(r0,r1)			MR(r0,r1)
#  define movi(r0,i0)			_movi(_jit,r0,i0)
static void _movi(jit_state_t*,jit_int32_t,jit_word_t);
#  define movi_p(r0,i0)			_movi_p(_jit,r0,i0)
static jit_word_t _movi_p(jit_state_t*,jit_int32_t,jit_word_t);
#  define negr(r0,r1)			NEG(r0,r1)
#  define comr(r0,r1)			NOT(r0,r1)
#  define extr_c(r0,r1)			EXTSB(r0,r1)
#  define extr_uc(r0,r1)		ANDI_(r0,r0,0xff)
#  define extr_s(r0,r1)			EXTSH(r0,r1)
#  define extr_us(r0,r1)		ANDI_(r0,r0,0xffff)
#  define addr(r0,r1,r2)		ADD(r0,r1,r2)
#  define addi(r0,r1,i0)		_addi(_jit,r0,r1,i0)
static void _addi(jit_state_t*,jit_int32_t,jit_int32_t,jit_word_t);
#  define addcr(r0,r1,r2)		ADDC(r0,r1,r2)
#  define addci(r0,r1,i0)		_addci(_jit,r0,r1,i0)
static void _addci(jit_state_t*,jit_int32_t,jit_int32_t,jit_word_t);
#  define addxr(r0,r1,r2)		ADDE(r0,r1,r2)
#  define addxi(r0,r1,i0)		_addxi(_jit,r0,r1,i0)
static void _addxi(jit_state_t*,jit_int32_t,jit_int32_t,jit_word_t);
#  define subr(r0,r1,r2)		SUB(r0,r1,r2)
#  define subi(r0,r1,i0)		_subi(_jit,r0,r1,i0)
static void _subi(jit_state_t*,jit_int32_t,jit_int32_t,jit_word_t);
#  define subcr(r0,r1,r2)		SUBC(r0,r1,r2)
#  define subci(r0,r1,i0)		_subci(_jit,r0,r1,i0)
static void _subci(jit_state_t*,jit_int32_t,jit_int32_t,jit_word_t);
#  define subxr(r0,r1,r2)		SUBFE(r0,r2,r1)
#  define subxi(r0,r1,i0)		_subxi(_jit,r0,r1,i0)
static void _subxi(jit_state_t*,jit_int32_t,jit_int32_t,jit_word_t);
#  define mulr(r0,r1,r2)		MULLW(r0,r1,r2)
#  define muli(r0,r1,i0)		_muli(_jit,r0,r1,i0)
static void _muli(jit_state_t*,jit_int32_t,jit_int32_t,jit_word_t);
#  define divr(r0,r1,r2)		DIVW(r0,r1,r2)
#  define divi(r0,r1,i0)		_divi(_jit,r0,r1,i0)
static void _divi(jit_state_t*,jit_int32_t,jit_int32_t,jit_word_t);
#  define divr_u(r0,r1,r2)		DIVWU(r0,r1,r2)
#  define divi_u(r0,r1,i0)		_divi_u(_jit,r0,r1,i0)
static void _divi_u(jit_state_t*,jit_int32_t,jit_int32_t,jit_word_t);

#  define andr(r0,r1,r2)		AND(r0,r1,r2)
#  define andi(r0,r1,i0)		_andi(_jit,r0,r1,i0)
static void _andi(jit_state_t*,jit_int32_t,jit_int32_t,jit_word_t);
#  define orr(r0,r1,r2)			OR(r0,r1,r2)
#  define ori(r0,r1,i0)			_ori(_jit,r0,r1,i0)
static void _ori(jit_state_t*,jit_int32_t,jit_int32_t,jit_word_t);
#  define xorr(r0,r1,r2)		XOR(r0,r1,r2)
#  define xori(r0,r1,i0)		_xori(_jit,r0,r1,i0)
static void _xori(jit_state_t*,jit_int32_t,jit_int32_t,jit_word_t);
#  define lshr(r0,r1,r2)		SLW(r0,r1,r2)
#  define lshi(r0,r1,i0)		SLWI(r0,r1,i0)
#  define rshr(r0,r1,r2)		SRAW(r0,r1,r2)
#  define rshi(r0,r1,i0)		SRAWI(r0,r1,i0)
#  define rshr_u(r0,r1,r2)		SRW(r0,r1,r2)
#  define rshi_u(r0,r1,i0)		SRWI(r0,r1,i0)

#  define ltr(r0,r1,r2)			_ltr(_jit,r0,r1,r2)
static void _ltr(jit_state_t*,jit_int32_t,jit_int32_t,jit_int32_t);
#  define lti(r0,r1,i0)			_lti(_jit,r0,r1,i0)
static void _lti(jit_state_t*,jit_int32_t,jit_int32_t,jit_word_t);
#  define ltr_u(r0,r1,r2)		_ltr_u(_jit,r0,r1,r2)
static void _ltr_u(jit_state_t*,jit_int32_t,jit_int32_t,jit_int32_t);
#  define lti_u(r0,r1,i0)		_lti_u(_jit,r0,r1,i0)
static void _lti_u(jit_state_t*,jit_int32_t,jit_int32_t,jit_word_t);
#  define ler(r0,r1,r2)			_ler(_jit,r0,r1,r2)
static void _ler(jit_state_t*,jit_int32_t,jit_int32_t,jit_int32_t);
#  define lei(r0,r1,i0)			_lei(_jit,r0,r1,i0)
static void _lei(jit_state_t*,jit_int32_t,jit_int32_t,jit_word_t);
#  define ler_u(r0,r1,r2)		_ler_u(_jit,r0,r1,r2)
static void _ler_u(jit_state_t*,jit_int32_t,jit_int32_t,jit_int32_t);
#  define lei_u(r0,r1,i0)		_lei_u(_jit,r0,r1,i0)
static void _lei_u(jit_state_t*,jit_int32_t,jit_int32_t,jit_word_t);
#  define eqr(r0,r1,r2)			_eqr(_jit,r0,r1,r2)
static void _eqr(jit_state_t*,jit_int32_t,jit_int32_t,jit_int32_t);
#  define eqi(r0,r1,i0)			_eqi(_jit,r0,r1,i0)
static void _eqi(jit_state_t*,jit_int32_t,jit_int32_t,jit_word_t);
#  define ger(r0,r1,r2)			_ger(_jit,r0,r1,r2)
static void _ger(jit_state_t*,jit_int32_t,jit_int32_t,jit_int32_t);
#  define gei(r0,r1,i0)			_gei(_jit,r0,r1,i0)
static void _gei(jit_state_t*,jit_int32_t,jit_int32_t,jit_word_t);
#  define ger_u(r0,r1,r2)		_ger_u(_jit,r0,r1,r2)
static void _ger_u(jit_state_t*,jit_int32_t,jit_int32_t,jit_int32_t);
#  define gei_u(r0,r1,i0)		_gei_u(_jit,r0,r1,i0)
static void _gei_u(jit_state_t*,jit_int32_t,jit_int32_t,jit_word_t);
#  define gtr(r0,r1,r2)			_gtr(_jit,r0,r1,r2)
static void _gtr(jit_state_t*,jit_int32_t,jit_int32_t,jit_int32_t);
#  define gti(r0,r1,i0)			_gti(_jit,r0,r1,i0)
static void _gti(jit_state_t*,jit_int32_t,jit_int32_t,jit_word_t);
#  define gtr_u(r0,r1,r2)		_gtr_u(_jit,r0,r1,r2)
static void _gtr_u(jit_state_t*,jit_int32_t,jit_int32_t,jit_int32_t);
#  define gti_u(r0,r1,i0)		_gti_u(_jit,r0,r1,i0)
static void _gti_u(jit_state_t*,jit_int32_t,jit_int32_t,jit_word_t);
#  define ner(r0,r1,r2)			_ner(_jit,r0,r1,r2)
static void _ner(jit_state_t*,jit_int32_t,jit_int32_t,jit_int32_t);
#  define nei(r0,r1,i0)			_nei(_jit,r0,r1,i0)
static void _nei(jit_state_t*,jit_int32_t,jit_int32_t,jit_word_t);

#define bltr(i0,r0,r1)			_bltr(_jit,i0,r0,r1)
static jit_word_t _bltr(jit_state_t*,jit_word_t,jit_int32_t,jit_int32_t);
#define blti(i0,r0,i1)			_blti(_jit,i0,r0,i1)
static jit_word_t _blti(jit_state_t*,jit_word_t,jit_int32_t,jit_word_t);
#define bltr_u(i0,r0,r1)		_bltr_u(_jit,i0,r0,r1)
static jit_word_t _bltr_u(jit_state_t*,jit_word_t,jit_int32_t,jit_int32_t);
#define blti_u(i0,r0,i1)		_blti_u(_jit,i0,r0,i1)
static jit_word_t _blti_u(jit_state_t*,jit_word_t,jit_int32_t,jit_word_t);
#define bler(i0,r0,r1)			_bler(_jit,i0,r0,r1)
static jit_word_t _bler(jit_state_t*,jit_word_t,jit_int32_t,jit_int32_t);
#define blei(i0,r0,i1)			_blei(_jit,i0,r0,i1)
static jit_word_t _blei(jit_state_t*,jit_word_t,jit_int32_t,jit_word_t);
#define bler_u(i0,r0,r1)		_bler_u(_jit,i0,r0,r1)
static jit_word_t _bler_u(jit_state_t*,jit_word_t,jit_int32_t,jit_int32_t);
#define blei_u(i0,r0,i1)		_blei_u(_jit,i0,r0,i1)
static jit_word_t _blei_u(jit_state_t*,jit_word_t,jit_int32_t,jit_word_t);
#define beqr(i0,r0,r1)			_beqr(_jit,i0,r0,r1)
static jit_word_t _beqr(jit_state_t*,jit_word_t,jit_int32_t,jit_int32_t);
#define beqi(i0,r0,i1)			_beqi(_jit,i0,r0,i1)
static jit_word_t _beqi(jit_state_t*,jit_word_t,jit_int32_t,jit_word_t);
#define bger(i0,r0,r1)			_bger(_jit,i0,r0,r1)
static jit_word_t _bger(jit_state_t*,jit_word_t,jit_int32_t,jit_int32_t);
#define bgei(i0,r0,i1)			_bgei(_jit,i0,r0,i1)
static jit_word_t _bgei(jit_state_t*,jit_word_t,jit_int32_t,jit_word_t);
#define bger_u(i0,r0,r1)		_bger_u(_jit,i0,r0,r1)
static jit_word_t _bger_u(jit_state_t*,jit_word_t,jit_int32_t,jit_int32_t);
#define bgei_u(i0,r0,i1)		_bgei_u(_jit,i0,r0,i1)
static jit_word_t _bgei_u(jit_state_t*,jit_word_t,jit_int32_t,jit_word_t);
#define bgtr(i0,r0,r1)			_bgtr(_jit,i0,r0,r1)
static jit_word_t _bgtr(jit_state_t*,jit_word_t,jit_int32_t,jit_int32_t);
#define bgti(i0,r0,i1)			_bgti(_jit,i0,r0,i1)
static jit_word_t _bgti(jit_state_t*,jit_word_t,jit_int32_t,jit_word_t);
#define bgtr_u(i0,r0,r1)		_bgtr_u(_jit,i0,r0,r1)
static jit_word_t _bgtr_u(jit_state_t*,jit_word_t,jit_int32_t,jit_int32_t);
#define bgti_u(i0,r0,i1)		_bgti_u(_jit,i0,r0,i1)
static jit_word_t _bgti_u(jit_state_t*,jit_word_t,jit_int32_t,jit_word_t);
#define bner(i0,r0,r1)			_bner(_jit,i0,r0,r1)
static jit_word_t _bner(jit_state_t*,jit_word_t,jit_int32_t,jit_int32_t);
#define bnei(i0,r0,i1)			_bnei(_jit,i0,r0,i1)
static jit_word_t _bnei(jit_state_t*,jit_word_t,jit_int32_t,jit_word_t);

#define boaddr(i0,r0,r1)		_boaddr(_jit,i0,r0,r1)
static jit_word_t _boaddr(jit_state_t*,jit_word_t,jit_int32_t,jit_int32_t);
#define boaddi(i0,r0,i1)		_boaddi(_jit,i0,r0,i1)
static jit_word_t _boaddi(jit_state_t*,jit_word_t,jit_int32_t,jit_word_t);
#define bxaddr(i0,r0,r1)		_bxaddr(_jit,i0,r0,r1)
static jit_word_t _bxaddr(jit_state_t*,jit_word_t,jit_int32_t,jit_int32_t);
#define bxaddi(i0,r0,i1)		_bxaddi(_jit,i0,r0,i1)
static jit_word_t _bxaddi(jit_state_t*,jit_word_t,jit_int32_t,jit_word_t);
#define bosubr(i0,r0,r1)		_bosubr(_jit,i0,r0,r1)
static jit_word_t _bosubr(jit_state_t*,jit_word_t,jit_int32_t,jit_int32_t);
#define bosubi(i0,r0,i1)		_bosubi(_jit,i0,r0,i1)
static jit_word_t _bosubi(jit_state_t*,jit_word_t,jit_int32_t,jit_word_t);
#define bxsubr(i0,r0,r1)		_bxsubr(_jit,i0,r0,r1)
static jit_word_t _bxsubr(jit_state_t*,jit_word_t,jit_int32_t,jit_int32_t);
#define bxsubi(i0,r0,i1)		_bxsubi(_jit,i0,r0,i1)
static jit_word_t _bxsubi(jit_state_t*,jit_word_t,jit_int32_t,jit_word_t);
#define boaddr_u(i0,r0,r1)		_boaddr_u(_jit,i0,r0,r1)
static jit_word_t _boaddr_u(jit_state_t*,jit_word_t,jit_int32_t,jit_int32_t);
#define boaddi_u(i0,r0,i1)		_boaddi_u(_jit,i0,r0,i1)
static jit_word_t _boaddi_u(jit_state_t*,jit_word_t,jit_int32_t,jit_word_t);
#define bxaddr_u(i0,r0,r1)		_bxaddr_u(_jit,i0,r0,r1)
static jit_word_t _bxaddr_u(jit_state_t*,jit_word_t,jit_int32_t,jit_int32_t);
#define bxaddi_u(i0,r0,i1)		_bxaddi_u(_jit,i0,r0,i1)
static jit_word_t _bxaddi_u(jit_state_t*,jit_word_t,jit_int32_t,jit_word_t);
#define bosubr_u(i0,r0,r1)		_bosubr_u(_jit,i0,r0,r1)
static jit_word_t _bosubr_u(jit_state_t*,jit_word_t,jit_int32_t,jit_int32_t);
#define bosubi_u(i0,r0,i1)		_bosubi_u(_jit,i0,r0,i1)
static jit_word_t _bosubi_u(jit_state_t*,jit_word_t,jit_int32_t,jit_word_t);
#define bxsubr_u(i0,r0,r1)		_bxsubr_u(_jit,i0,r0,r1)
static jit_word_t _bxsubr_u(jit_state_t*,jit_word_t,jit_int32_t,jit_int32_t);
#define bxsubi_u(i0,r0,i1)		_bxsubi_u(_jit,i0,r0,i1)
static jit_word_t _bxsubi_u(jit_state_t*,jit_word_t,jit_int32_t,jit_word_t);

#  define ldr_c(r0,r1)			_ldr_c(_jit,r0,r1)
static void _ldr_c(jit_state_t*,jit_int32_t,jit_int32_t);
#  define ldi_c(r0,i0)			_ldi_c(_jit,r0,i0)
static void _ldi_c(jit_state_t*,jit_int32_t,jit_word_t);
#  define ldxr_c(r0,r1,i0)		_ldxr_c(_jit,r0,r1,i0)
static void _ldxr_c(jit_state_t*,jit_int32_t,jit_int32_t,jit_word_t);
#  define ldxi_c(r0,r1,i0)		_ldxi_c(_jit,r0,r1,i0)
static void _ldxi_c(jit_state_t*,jit_int32_t,jit_int32_t,jit_word_t);
#  define ldr_uc(r0,r1)			LBZX(r0, _R0_REGNO, r1)
#  define ldi_uc(r0,i0)			_ldi_uc(_jit,r0,i0)
static void _ldi_uc(jit_state_t*,jit_int32_t,jit_word_t);
#  define ldxr_uc(r0,r1,r2)		_ldxr_uc(_jit,r0,r1,r2)
static void _ldxr_uc(jit_state_t*,jit_int32_t,jit_int32_t,jit_int32_t);
#  define ldxi_uc(r0,r1,i0)		_ldxi_uc(_jit,r0,r1,i0)
static void _ldxi_uc(jit_state_t*,jit_int32_t,jit_int32_t,jit_word_t);
#  define ldr_s(r0,r1)			LHAX(r0, _R0_REGNO, r1)
#  define ldi_s(r0,i0)			_ldi_s(_jit,r0,i0)
static void _ldi_s(jit_state_t*,jit_int32_t,jit_word_t);
#  define ldxr_s(r0,r1,i0)		_ldxr_s(_jit,r0,r1,i0)
static void _ldxr_s(jit_state_t*,jit_int32_t,jit_int32_t,jit_word_t);
#  define ldxi_s(r0,r1,i0)		_ldxi_s(_jit,r0,r1,i0)
static void _ldxi_s(jit_state_t*,jit_int32_t,jit_int32_t,jit_word_t);
#  define ldr_us(r0,r1)			LHZX(r0, _R0_REGNO, r1)
#  define ldi_us(r0,i0)			_ldi_us(_jit,r0,i0)
static void _ldi_us(jit_state_t*,jit_int32_t,jit_word_t);
#  define ldxr_us(r0,r1,i0)		_ldxr_us(_jit,r0,r1,i0)
static void _ldxr_us(jit_state_t*,jit_int32_t,jit_int32_t,jit_word_t);
#  define ldxi_us(r0,r1,i0)		_ldxi_us(_jit,r0,r1,i0)
static void _ldxi_us(jit_state_t*,jit_int32_t,jit_int32_t,jit_word_t);
#  define ldr_i(r0,r1)			LWZX(r0, _R0_REGNO, r1)
#  define ldi_i(r0,i0)			_ldi_i(_jit,r0,i0)
static void _ldi_i(jit_state_t*,jit_int32_t,jit_word_t);
#  define ldxr_i(r0,r1,i0)		_ldxr_i(_jit,r0,r1,i0)
static void _ldxr_i(jit_state_t*,jit_int32_t,jit_int32_t,jit_word_t);
#  define ldxi_i(r0,r1,i0)		_ldxi_i(_jit,r0,r1,i0)
static void _ldxi_i(jit_state_t*,jit_int32_t,jit_int32_t,jit_word_t);
#  define str_c(r0,r1)			STBX(r1, _R0_REGNO, r0)
#  define sti_c(i0,r0)			_sti_c(_jit,i0,r0)
static void _sti_c(jit_state_t*,jit_word_t,jit_int32_t);
#  define stxr_c(r0,r1,r2)		_stxr_c(_jit,r0,r1,r2)
static void _stxr_c(jit_state_t*,jit_int32_t,jit_int32_t,jit_int32_t);
#  define stxi_c(i0,r0,r1)		_stxi_c(_jit,i0,r0,r1)
static void _stxi_c(jit_state_t*,jit_word_t,jit_int32_t,jit_int32_t);
#  define str_s(r0,r1)			STHX(r1, _R0_REGNO, r0)
#  define sti_s(i0,r0)			_sti_s(_jit,i0,r0)
static void _sti_s(jit_state_t*,jit_word_t,jit_int32_t);
#  define stxr_s(r0,r1,r2)		_stxr_s(_jit,r0,r1,r2)
static void _stxr_s(jit_state_t*,jit_int32_t,jit_int32_t,jit_int32_t);
#  define stxi_s(i0,r0,r1)		_stxi_s(_jit,i0,r0,r1)
static void _stxi_s(jit_state_t*,jit_word_t,jit_int32_t,jit_int32_t);
#  define str_i(r0,r1)			STWX(r1, _R0_REGNO, r0)
#  define sti_i(i0,r0)			_sti_i(_jit,i0,r0)
static void _sti_i(jit_state_t*,jit_word_t,jit_int32_t);
#  define stxr_i(r0,r1,r2)		_stxr_i(_jit,r0,r1,r2)
static void _stxr_i(jit_state_t*,jit_int32_t,jit_int32_t,jit_int32_t);
#  define stxi_i(i0,r0,r1)		_stxi_i(_jit,i0,r0,r1)
static void _stxi_i(jit_state_t*,jit_word_t,jit_int32_t,jit_int32_t);
#  define jmpr(r0)			_jmpr(_jit,r0)
static void _jmpr(jit_state_t*,jit_int32_t);
#  define jmpi(i0)			_jmpi(_jit,i0)
static jit_word_t _jmpi(jit_state_t*,jit_word_t);
#  define jmpi_p(i0)			_jmpi_p(_jit,i0)
static jit_word_t _jmpi_p(jit_state_t*,jit_word_t) maybe_unused;
#  define callr(r0)			_callr(_jit,r0)
static void _callr(jit_state_t*,jit_int32_t);
#  define calli(i0)			_calli(_jit,i0)
static jit_word_t _calli(jit_state_t*,jit_word_t);
#  define calli_p(i0)			_calli_p(_jit,i0)
static jit_word_t _calli_p(jit_state_t*,jit_word_t);
#  define prolog(node)			_prolog(_jit, node)
static void _prolog(jit_state_t*, jit_node_t*);
#  define epilog(node)			_epilog(_jit, node)
static void _epilog(jit_state_t*, jit_node_t*);
#  define patch_at(i,l)			_patch_at(_jit,i,l)
static void _patch_at(jit_state_t*,jit_word_t,jit_word_t);
#endif

#if CODE
#  define _u16(v)			((v) & 0xffff)
#  define _u26(v)			((v) & 0x3ffffff)
static void
_FXO(jit_state_t *_jit, int o, int d, int a, int b, int e, int x, int r)
{
    assert(!(o & ~((1 << 6) - 1)));
    assert(!(d & ~((1 << 5) - 1)));
    assert(!(a & ~((1 << 5) - 1)));
    assert(!(b & ~((1 << 5) - 1)));
    assert(!(e & ~((1 << 1) - 1)));
    assert(!(x & ~((1 << 9) - 1)));
    assert(!(r & ~((1 << 1) - 1)));
    ii((o<<26)|(d<<21)|(a<<16)|(b<<11)|(e<<10)|(x<<1)|r);
}

static void
_FDs(jit_state_t *_jit, int o, int d, int a, int s)
{
    assert(!(o & ~((1 << 6) - 1)));
    assert(!(d & ~((1 << 5) - 1)));
    assert(!(a & ~((1 << 5) - 1)));
    assert(can_sign_extend_short_p(s));
    ii((o<<26)|(d<<21)|(a<<16)|_u16(s));
}

static void
_FDu(jit_state_t *_jit, int o, int d, int a, int s)
{
    assert(!(o & ~((1 << 6) - 1)));
    assert(!(d & ~((1 << 5) - 1)));
    assert(!(a & ~((1 << 5) - 1)));
    assert(can_zero_extend_short_p(s));
    ii((o<<26)|(d<<21)|(a<<16)|_u16(s));
}

static void
_FX(jit_state_t *_jit, int o, int s, int a, int b, int x, int r)
{
    assert(!(o & ~((1 <<  6) - 1)));
    assert(!(s & ~((1 <<  5) - 1)));
    assert(!(a & ~((1 <<  5) - 1)));
    assert(!(b & ~((1 <<  5) - 1)));
    assert(!(x & ~((1 << 10) - 1)));
    assert(!(r & ~((1 <<  1) - 1)));
    ii((o<<26)|(s<<21)|(a<<16)|(b<<11)|(x<<1)|r);
}

static void
_FI(jit_state_t *_jit, int o, int t, int a, int k)
{
    assert(!(o & ~(( 1 <<  6) - 1)));
    assert(!(t & 3) && can_sign_extend_jump_p(t));
    assert(!(a & ~(( 1 <<  1) - 1)));
    assert(!(k & ~(( 1 <<  1) - 1)));
    ii((o<<26)|_u26(t)|(a<<1)|k);
}

static void
_FB(jit_state_t *_jit, int o, int bo, int bi, int t, int a, int k)
{
    assert(!( o & ~((1 <<  6) - 1)));
    assert(!(bo & ~((1 <<  5) - 1)));
    assert(!(bi & ~((1 <<  5) - 1)));
    assert(!(t & 3) && can_sign_extend_short_p(t));
    assert(!(a & ~(( 1 <<  1) - 1)));
    assert(!(k & ~(( 1 <<  1) - 1)));
    ii((o<<26)|(bo<<21)|(bi<<16)|_u16(t)|(a<<1)|k);
}

static void
_FXL(jit_state_t *_jit, int o, int bo, int bi, int x, int k)
{
    assert(!( o & ~((1 <<  6) - 1)));
    assert(!(bo & ~((1 <<  5) - 1)));
    assert(!(bi & ~((1 <<  5) - 1)));
    assert(!(x & ~(( 1 << 10) - 1)));
    assert(!(k & ~(( 1 <<  1) - 1)));
    ii((o<<26)|(bo<<21)|(bi<<16)|(x<<1)|k);
}

static void
_FC(jit_state_t *_jit, int o, int d, int l, int a, int b, int x)
{
    assert(!(o & ~((1 <<  6) - 1)));
    assert(!(d & ~((1 <<  3) - 1)));
    assert(!(l & ~((1 <<  1) - 1)));
    assert(!(a & ~((1 <<  5) - 1)));
    assert(!(b & ~((1 <<  5) - 1)));
    assert(!(x & ~((1 << 10) - 1)));
    ii((o<<26)|(d<<23)|(l<<21)|(a<<16)|(b<<11)|(x<<1));
}

static void
_FCI(jit_state_t *_jit, int o, int d, int l, int a, int s)
{
    assert(!(o & ~((1 << 6) - 1)));
    assert(!(d & ~((1 << 3) - 1)));
    assert(!(l & ~((1 << 1) - 1)));
    assert(!(a & ~((1 << 5) - 1)));
    if (o == 11)	assert(can_sign_extend_short_p(s));
    else if (o == 10)	assert(can_zero_extend_short_p(s));
#if DEBUG
    else		abort();
#endif
    ii((o<<26)|(d<<23)|(l<<21)|(a<<16)|_u16(s));
}

static void
_FXFX(jit_state_t *_jit, int o, int d, int x, int f)
{
    assert(!(o & ~((1 <<  6) - 1)));
    assert(!(d & ~((1 <<  5) - 1)));
    assert(!(x & ~((1 << 10) - 1)));
    assert(!(f & ~((1 << 10) - 1)));
    ii((o<<26)|(d<<21)|(x<<11)|(f<<1));
}

static void
_FM(jit_state_t *_jit, int o, int s, int a, int h, int b, int e, int r)
{
    assert(!(o & ~((1 << 6) - 1)));
    assert(!(s & ~((1 << 5) - 1)));
    assert(!(a & ~((1 << 5) - 1)));
    assert(!(h & ~((1 << 5) - 1)));
    assert(!(b & ~((1 << 5) - 1)));
    assert(!(e & ~((1 << 5) - 1)));
    assert(!(r & ~((1 << 1) - 1)));
    ii((o<<26)|(s<<21)|(a<<16)|(h<<11)|(b<<6)|(e<<1)|r);
}

static void
_movi(jit_state_t *_jit, jit_int32_t r0, jit_word_t i0)
{
    if (can_sign_extend_short_p(i0))
	LI(r0, i0);
    else {
	LIS(r0, i0 >> 16);
	if ((jit_uint16_t)i0)
	    ORI(r0, r0, (jit_uint16_t)i0);
    }
}

static jit_word_t
_movi_p(jit_state_t *_jit, jit_int32_t r0, jit_word_t i0)
{
    jit_word_t		word = _jit->pc.w;
    LIS(r0, i0 >> 16);
    ORI(r0, r0, (jit_uint16_t)i0);
    return (word);
}

static void
_addi(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_word_t i0)
{
    jit_int32_t		reg;
    if (can_sign_extend_short_p(i0))
	ADDI(r0, r1, i0);
    else if (!(i0 & 0x0000ffff))
	ADDIS(r0, r1, i0 >> 16);
    else {
	reg = jit_get_reg(jit_class_gpr);
	movi(rn(reg), i0);
	ADD(r0, r1, rn(reg));
	jit_unget_reg(reg);
    }
}

static void
_addci(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_word_t i0)
{
    jit_int32_t		reg;
    if (can_sign_extend_short_p(i0))
	ADDIC(r0, r1, i0);
    else {
	reg = jit_get_reg(jit_class_gpr);
	movi(rn(reg), i0);
	ADDC(r0, r1, rn(reg));
	jit_unget_reg(reg);
    }
}

static void
_addxi(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_word_t i0)
{
    jit_int32_t		reg;
    reg = jit_get_reg(jit_class_gpr);
    movi(rn(reg), i0);
    ADDE(r0, r1, rn(reg));
    jit_unget_reg(reg);
}

static void
_subi(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_word_t i0)
{
    jit_int32_t		reg;
    jit_word_t		ni0 = -i0;
    if (can_sign_extend_short_p(ni0))
	ADDI(r0, r1, ni0);
    else if (!(ni0 & 0x0000ffff))
	ADDIS(r0, r1, ni0 >> 16);
    else {
	reg = jit_get_reg(jit_class_gpr);
	movi(rn(reg), i0);
	SUB(r0, r1, rn(reg));
	jit_unget_reg(reg);
    }
}

static void
_subci(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_word_t i0)
{
    jit_int32_t		reg;
    reg = jit_get_reg(jit_class_gpr);
    movi(rn(reg), i0);
    SUBC(r0, r1, rn(reg));
    jit_unget_reg(reg);
}

static void
_subxi(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_word_t i0)
{
    jit_int32_t		reg;
    reg = jit_get_reg(jit_class_gpr);
    movi(rn(reg), i0);
    SUBE(r0, r1, rn(reg));
    jit_unget_reg(reg);
}

static void
_muli(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_word_t i0)
{
    jit_int32_t		reg;
    if (can_sign_extend_short_p(i0))
	MULLI(r0, r1, i0);
    else {
	reg = jit_get_reg(jit_class_gpr);
	movi(rn(reg), i0);
	MULLW(r0, r1, rn(reg));
	jit_unget_reg(reg);
    }
}

static void
_divi(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_word_t i0)
{
    jit_int32_t		reg;
    reg = jit_get_reg(jit_class_gpr);
    movi(rn(reg), i0);
    DIVW(r0, r1, rn(reg));
    jit_unget_reg(reg);
}

static void
_divi_u(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_word_t i0)
{
    jit_int32_t		reg;
    reg = jit_get_reg(jit_class_gpr);
    movi(rn(reg), i0);
    DIVWU(r0, r1, rn(reg));
    jit_unget_reg(reg);
}

static void
_andi(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_word_t i0)
{
    jit_int32_t		reg;
    if (can_zero_extend_short_p(i0))
	ANDI_(r0, r1, i0);
    else if (!(i0 & 0x0000ffff))
	ANDIS_(r0, r1, i0 >> 16);
    else {
	reg = jit_get_reg(jit_class_gpr);
	movi(rn(reg), i0);
	AND(r0, r1, rn(reg));
	jit_unget_reg(reg);
    }
}

static void
_ori(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_word_t i0)
{
    jit_int32_t		reg;
    if (can_zero_extend_short_p(i0))
	ORI(r0, r1, i0);
    else if (!(i0 & 0x0000ffff))
	ORIS(r0, r1, i0 >> 16);
    else {
	reg = jit_get_reg(jit_class_gpr);
	movi(rn(reg), i0);
	OR(r0, r1, rn(reg));
	jit_unget_reg(reg);
    }
}

static void
_xori(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_word_t i0)
{
    jit_int32_t		reg;
    if (can_zero_extend_short_p(i0))
	XORI(r0, r1, i0);
    else if (!(i0 & 0x0000ffff))
	XORIS(r0, r1, i0 >> 16);
    else {
	reg = jit_get_reg(jit_class_gpr);
	movi(rn(reg), i0);
	XOR(r0, r1, rn(reg));
	jit_unget_reg(reg);
    }
}

static void
_ltr(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_int32_t r2)
{
    CMPW(r1, r2);
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_LT);
}

static void
_lti(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_word_t i0)
{
    jit_int32_t		reg;
    if (can_sign_extend_short_p(i0))
	CMPWI(r1, i0);
    else {
	reg = jit_get_reg(jit_class_gpr);
	movi(rn(reg), i0);
	CMPW(r1, rn(reg));
	jit_unget_reg(reg);
    }
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_LT);
}

static void
_ltr_u(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_int32_t r2)
{
    CMPLW(r1, r2);
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_LT);
}

static void
_lti_u(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_word_t i0)
{
    jit_int32_t		reg;
    if (can_zero_extend_short_p(i0))
	CMPLWI(r1, i0);
    else {
	reg = jit_get_reg(jit_class_gpr);
	movi(rn(reg), i0);
	CMPLW(r1, rn(reg));
	jit_unget_reg(reg);
    }
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_LT);
}

static void
_ler(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_int32_t r2)
{
    CMPW(r1, r2);
    CRNOT(CR_GT, CR_GT);
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_GT);
}

static void
_lei(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_word_t i0)
{
    jit_int32_t		reg;
    if (can_sign_extend_short_p(i0))
	CMPWI(r1, i0);
    else {
	reg = jit_get_reg(jit_class_gpr);
	movi(rn(reg), i0);
	CMPW(r1, rn(reg));
	jit_unget_reg(reg);
    }
    CRNOT(CR_GT, CR_GT);
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_GT);
}

static void
_ler_u(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_int32_t r2)
{
    CMPLW(r1, r2);
    CRNOT(CR_GT, CR_GT);
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_GT);
}

static void
_lei_u(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_word_t i0)
{
    jit_int32_t		reg;
    if (can_zero_extend_short_p(i0))
	CMPLWI(r1, i0);
    else {
	reg = jit_get_reg(jit_class_gpr);
	movi(rn(reg), i0);
	CMPLW(r1, rn(reg));
	jit_unget_reg(reg);
    }
    CRNOT(CR_GT, CR_GT);
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_GT);
}

static void
_eqr(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_int32_t r2)
{
    CMPW(r1, r2);
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_EQ);
}

static void
_eqi(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_word_t i0)
{
    jit_int32_t		reg;
    if (can_sign_extend_short_p(i0))
	CMPWI(r1, i0);
    else if (can_zero_extend_short_p(i0))
	CMPLWI(r1, i0);
    else {
	reg = jit_get_reg(jit_class_gpr);
	movi(rn(reg), i0);
	CMPW(r1, rn(reg));
	jit_unget_reg(reg);
    }
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_EQ);
}

static void
_ger(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_int32_t r2)
{
    CMPW(r1, r2);
    CRNOT(CR_LT, CR_LT);
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_LT);
}

static void
_gei(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_word_t i0)
{
    jit_int32_t		reg;
    if (can_sign_extend_short_p(i0))
	CMPWI(r1, i0);
    else {
	reg = jit_get_reg(jit_class_gpr);
	movi(rn(reg), i0);
	CMPW(r1, rn(reg));
	jit_unget_reg(reg);
    }
    CRNOT(CR_LT, CR_LT);
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_LT);
}

static void
_ger_u(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_int32_t r2)
{
    CMPLW(r1, r2);
    CRNOT(CR_LT, CR_LT);
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_LT);
}

static void
_gei_u(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_word_t i0)
{
    jit_int32_t		reg;
    if (can_zero_extend_short_p(i0))
	CMPLWI(r1, i0);
    else {
	reg = jit_get_reg(jit_class_gpr);
	movi(rn(reg), i0);
	CMPLW(r1, rn(reg));
	jit_unget_reg(reg);
    }
    CRNOT(CR_LT, CR_LT);
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_LT);
}

static void
_gtr(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_int32_t r2)
{
    CMPW(r1, r2);
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_GT);
}

static void
_gti(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_word_t i0)
{
    jit_int32_t		reg;
    if (can_sign_extend_short_p(i0))
	CMPWI(r1, i0);
    else {
	reg = jit_get_reg(jit_class_gpr);
	movi(rn(reg), i0);
	CMPW(r1, rn(reg));
	jit_unget_reg(reg);
    }
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_GT);
}

static void
_gtr_u(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_int32_t r2)
{
    CMPLW(r1, r2);
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_GT);
}

static void
_gti_u(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_word_t i0)
{
    jit_int32_t		reg;
    if (can_zero_extend_short_p(i0))
	CMPLWI(r1, i0);
    else {
	reg = jit_get_reg(jit_class_gpr);
	movi(rn(reg), i0);
	CMPLW(r1, rn(reg));
	jit_unget_reg(reg);
    }
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_GT);
}

static void
_ner(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_int32_t r2)
{
    CMPW(r1, r2);
    CRNOT(CR_EQ, CR_EQ);
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_EQ);
}

static void
_nei(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_word_t i0)
{
    jit_int32_t		reg;
    if (can_sign_extend_short_p(i0))
	CMPWI(r1, i0);
    else if (can_zero_extend_short_p(i0))
	CMPLWI(r1, i0);
    else {
	reg = jit_get_reg(jit_class_gpr);
	movi(rn(reg), i0);
	CMPW(r1, rn(reg));
	jit_unget_reg(reg);
    }
    CRNOT(CR_EQ, CR_EQ);
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_EQ);
}

static jit_word_t
_bltr(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_int32_t r1)
{
    jit_word_t		d, w;
    CMPW(r0, r1);
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BLT(d);
    return (w);
}

static jit_word_t
_blti(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_word_t i1)
{
    jit_int32_t		reg;
    jit_word_t		d, w;
    if (can_sign_extend_short_p(i1))
	CMPWI(r0, i1);
    else {
	reg = jit_get_reg(jit_class_gpr);
	movi(rn(reg), i1);
	CMPW(r0, rn(reg));
	jit_unget_reg(reg);
    }
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BLT(d);
    return (w);
}

static jit_word_t
_bltr_u(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_int32_t r1)
{
    jit_word_t		d, w;
    CMPLW(r0, r1);
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BLT(d);
    return (w);
}

static jit_word_t
_blti_u(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_word_t i1)
{
    jit_int32_t		reg;
    jit_word_t		d, w;
    if (can_zero_extend_short_p(i1))
	CMPLWI(r0, i1);
    else {
	reg = jit_get_reg(jit_class_gpr);
	movi(rn(reg), i1);
	CMPLW(r0, rn(reg));
	jit_unget_reg(reg);
    }
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BLT(d);
    return (w);
}

static jit_word_t
_bler(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_int32_t r1)
{
    jit_word_t		d, w;
    CMPW(r0, r1);
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BLE(d);
    return (w);
}

static jit_word_t
_blei(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_word_t i1)
{
    jit_int32_t		reg;
    jit_word_t		d, w;
    if (can_sign_extend_short_p(i1))
	CMPWI(r0, i1);
    else {
	reg = jit_get_reg(jit_class_gpr);
	movi(rn(reg), i1);
	CMPW(r0, rn(reg));
	jit_unget_reg(reg);
    }
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BLE(d);
    return (w);
}

static jit_word_t
_bler_u(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_int32_t r1)
{
    jit_word_t		d, w;
    CMPLW(r0, r1);
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BLE(d);
    return (w);
}

static jit_word_t
_blei_u(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_word_t i1)
{
    jit_int32_t		reg;
    jit_word_t		d, w;
    if (can_zero_extend_short_p(i1))
	CMPLWI(r0, i1);
    else {
	reg = jit_get_reg(jit_class_gpr);
	movi(rn(reg), i1);
	CMPLW(r0, rn(reg));
	jit_unget_reg(reg);
    }
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BLE(d);
    return (w);
}

static jit_word_t
_beqr(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_int32_t r1)
{
    jit_word_t		d, w;
    CMPW(r0, r1);
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BEQ(d);
    return (w);
}

static jit_word_t
_beqi(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_word_t i1)
{
    jit_int32_t		reg;
    jit_word_t		d, w;
    if (can_sign_extend_short_p(i1))
	CMPWI(r0, i1);
    else if (can_zero_extend_short_p(i1))
	CMPLWI(r0, i1);
    else {
	reg = jit_get_reg(jit_class_gpr);
	movi(rn(reg), i1);
	CMPW(r0, rn(reg));
	jit_unget_reg(reg);
    }
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BEQ(d);
    return (w);
}

static jit_word_t
_bger(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_int32_t r1)
{
    jit_word_t		d, w;
    CMPW(r0, r1);
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BGE(d);
    return (w);
}

static jit_word_t
_bgei(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_word_t i1)
{
    jit_int32_t		reg;
    jit_word_t		d, w;
    if (can_sign_extend_short_p(i1))
	CMPWI(r0, i1);
    else {
	reg = jit_get_reg(jit_class_gpr);
	movi(rn(reg), i1);
	CMPW(r0, rn(reg));
	jit_unget_reg(reg);
    }
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BGE(d);
    return (w);
}

static jit_word_t
_bger_u(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_int32_t r1)
{
    jit_word_t		d, w;
    CMPLW(r0, r1);
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BGE(d);
    return (w);
}

static jit_word_t
_bgei_u(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_word_t i1)
{
    jit_int32_t		reg;
    jit_word_t		d, w;
    if (can_zero_extend_short_p(i1))
	CMPLWI(r0, i1);
    else {
	reg = jit_get_reg(jit_class_gpr);
	movi(rn(reg), i1);
	CMPLW(r0, rn(reg));
	jit_unget_reg(reg);
    }
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BGE(d);
    return (w);
}

static jit_word_t
_bgtr(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_int32_t r1)
{
    jit_word_t		d, w;
    CMPW(r0, r1);
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BGT(d);
    return (w);
}

static jit_word_t
_bgti(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_word_t i1)
{
    jit_int32_t		reg;
    jit_word_t		d, w;
    if (can_sign_extend_short_p(i1))
	CMPWI(r0, i1);
    else {
	reg = jit_get_reg(jit_class_gpr);
	movi(rn(reg), i1);
	CMPW(r0, rn(reg));
	jit_unget_reg(reg);
    }
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BGT(d);
    return (w);
}

static jit_word_t
_bgtr_u(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_int32_t r1)
{
    jit_word_t		d, w;
    CMPLW(r0, r1);
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BGT(d);
    return (w);
}

static jit_word_t
_bgti_u(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_word_t i1)
{
    jit_int32_t		reg;
    jit_word_t		d, w;
    if (can_zero_extend_short_p(i1))
	CMPLWI(r0, i1);
    else {
	reg = jit_get_reg(jit_class_gpr);
	movi(rn(reg), i1);
	CMPLW(r0, rn(reg));
	jit_unget_reg(reg);
    }
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BGT(d);
    return (w);
}

static jit_word_t
_bner(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_int32_t r1)
{
    jit_word_t		d, w;
    CMPW(r0, r1);
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BNE(d);
    return (w);
}

static jit_word_t
_bnei(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_word_t i1)
{
    jit_int32_t		reg;
    jit_word_t		d, w;
    if (can_sign_extend_short_p(i1))
	CMPWI(r0, i1);
    else if (can_zero_extend_short_p(i1))
	CMPLWI(r0, i1);
    else {
	reg = jit_get_reg(jit_class_gpr);
	movi(rn(reg), i1);
	CMPW(r0, rn(reg));
	jit_unget_reg(reg);
    }
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BNE(d);
    return (w);
}

static jit_word_t
_boaddr(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_int32_t r1)
{
    jit_word_t		d, w;
    ADDO(r0, r0, r1);
    MCRXR(CR_0);
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BGT(d);				/* GT = bit 1 of XER = OV */
    return (w);
}

static jit_word_t
_boaddi(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_word_t i1)
{
    jit_word_t		w;
    jit_int32_t		reg;
    reg = jit_get_reg(jit_class_gpr);
    movi(rn(reg), i1);
    w = boaddr(i0, r0, rn(reg));
    jit_unget_reg(reg);
    return (w);
}

static jit_word_t
_bxaddr(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_int32_t r1)
{
    jit_word_t		d, w;
    ADDO(r0, r0, r1);
    MCRXR(CR_0);
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BLE(d);
    return (w);
}

static jit_word_t
_bxaddi(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_word_t i1)
{
    jit_word_t		w;
    jit_int32_t		reg;
    reg = jit_get_reg(jit_class_gpr);
    movi(rn(reg), i1);
    w = bxaddr(i0, r0, rn(reg));
    jit_unget_reg(reg);
    return (w);
}

static jit_word_t
_bosubr(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_int32_t r1)
{
    jit_word_t		d, w;
    SUBO(r0, r0, r1);
    MCRXR(CR_0);
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BGT(d);
    return (w);
}

static jit_word_t
_bosubi(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_word_t i1)
{
    jit_word_t		w;
    jit_int32_t		reg;
    reg = jit_get_reg(jit_class_gpr);
    movi(rn(reg), i1);
    w = bosubr(i0, r0, rn(reg));
    jit_unget_reg(reg);
    return (w);
}

static jit_word_t
_bxsubr(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_int32_t r1)
{
    jit_word_t		d, w;
    SUBO(r0, r0, r1);
    MCRXR(CR_0);
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BLE(d);
    return (w);
}

static jit_word_t
_bxsubi(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_word_t i1)
{
    jit_word_t		w;
    jit_int32_t		reg;
    reg = jit_get_reg(jit_class_gpr);
    movi(rn(reg), i1);
    w = bxsubr(i0, r0, rn(reg));
    jit_unget_reg(reg);
    return (w);
}

static jit_word_t
_boaddr_u(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_int32_t r1)
{
    jit_word_t		d, w;
    ADDC(r0, r0, r1);
    MCRXR(CR_0);
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BEQ(d);				/* EQ = bit 2 of XER = CA */
    return (w);
}

static jit_word_t
_boaddi_u(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_word_t i1)
{
    jit_int32_t		reg;
    jit_word_t		d, w;
    if (can_sign_extend_short_p(i1)) {
	ADDIC(r0, r0, i1);
	MCRXR(CR_0);
	w = _jit->pc.w;
	d = (i0 - w) & ~3;
	BEQ(d);
	return (w);
    }
    reg = jit_get_reg(jit_class_gpr);
    movi(rn(reg), i1);
    w = boaddr_u(i0, r0, rn(reg));
    jit_unget_reg(reg);
    return (w);
}

static jit_word_t
_bxaddr_u(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_int32_t r1)
{
    jit_word_t		d, w;
    ADDC(r0, r0, r1);
    MCRXR(CR_0);
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BNE(d);
    return (w);
}

static jit_word_t
_bxaddi_u(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_word_t i1)
{
    jit_int32_t		reg;
    jit_word_t		d, w;
    if (can_sign_extend_short_p(i1)) {
	ADDIC(r0, r0, i1);
	MCRXR(CR_0);
	w = _jit->pc.w;
	d = (i0 - w) & ~3;
	BNE(d);
	return (w);
    }
    reg = jit_get_reg(jit_class_gpr);
    movi(rn(reg), i1);
    w = bxaddr_u(i0, r0, rn(reg));
    jit_unget_reg(reg);
    return (w);
}

static jit_word_t
_bosubr_u(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_int32_t r1)
{
    jit_word_t		d, w;
    SUBC(r0, r0, r1);
    MCRXR(CR_0);
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BNE(d);				/* PPC uses "carry" not "borrow" */
    return (w);
}

static jit_word_t
_bosubi_u(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_word_t i1)
{
    jit_word_t		w;
    jit_int32_t		reg;
    reg = jit_get_reg(jit_class_gpr);
    movi(rn(reg), i1);
    w = bosubr_u(i0, r0, rn(reg));
    jit_unget_reg(reg);
    return (w);
}

static jit_word_t
_bxsubr_u(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_int32_t r1)
{
    jit_word_t		d, w;
    SUBC(r0, r0, r1);
    MCRXR(CR_0);
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BEQ(d);
    return (w);
}

static jit_word_t
_bxsubi_u(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_word_t i1)
{
    jit_word_t		w;
    jit_int32_t		reg;
    reg = jit_get_reg(jit_class_gpr);
    movi(rn(reg), i1);
    w = bxsubr_u(i0, r0, rn(reg));
    jit_unget_reg(reg);
    return (w);
}

static void
_ldr_c(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1)
{
    ldr_uc(r0, r1);
    extr_c(r0, r0);
}

static void
_ldi_c(jit_state_t *_jit, jit_int32_t r0, jit_word_t i0)
{
    ldi_c(r0, i0);
    extr_c(r0, r0);
}

static void
_ldxr_c(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_int32_t r2)
{
    ldxr_uc(r0, r1, r2);
    extr_c(r0, r0);
}

static void
_ldxi_c(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_word_t i0)
{
    ldxi_uc(r0, r1, i0);
    extr_c(r0, r0);
}

static void
_ldi_uc(jit_state_t *_jit, jit_int32_t r0, jit_word_t i0)
{
    jit_bool_t		inv;
    jit_int32_t		reg;
    jit_word_t		lo, hi;
    if (can_sign_extend_short_p(i0))
	LBZ(r0, _R0_REGNO, i0);
    else {
	hi = (i0 >> 16) + ((jit_uint16_t)i0 >> 15);
	lo = (jit_int16_t)(i0 - (hi << 16));
	reg = jit_get_reg(jit_class_gpr);
	if ((inv = reg == _R0))		reg = jit_get_reg(jit_class_gpr);
	LIS(rn(reg), hi);
	LBZ(r0, rn(reg), lo);
	jit_unget_reg(reg);
	if (inv)			jit_unget_reg(_R0);
    }
}

static void
_ldxr_uc(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_int32_t r2)
{
    jit_int32_t		reg;
    if (r1 == _R0_REGNO) {
	if (r2 != _R0_REGNO)
	    LBZX(r0, r2, r1);
	else {
	    reg = jit_get_reg(jit_class_gpr);
	    movr(rn(reg), r1);
	    LBZX(r0, rn(reg), r2);
	    jit_unget_reg(reg);
	}
    }
    else
	LBZX(r0, r1, r2);
}

static void
_ldxi_uc(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_word_t i0)
{
    jit_int32_t		reg;
    if (i0 == 0)
	ldr_uc(r0, r1);
    else if (can_sign_extend_short_p(i0)) {
	if (r1 == _R0_REGNO) {
	    reg = jit_get_reg(jit_class_gpr);
	    movr(rn(reg), r1);
	    LBZ(r0, rn(reg), i0);
	    jit_unget_reg(reg);
	}
	else
	    LBZ(r0, r1, i0);
    }
    else {
	reg = jit_get_reg(jit_class_gpr);
	movi(rn(reg), i0);
	ldxr_uc(r0, r1, rn(reg));
	jit_unget_reg(reg);
    }
}

static void
_ldi_s(jit_state_t *_jit, jit_int32_t r0, jit_word_t i0)
{
    jit_bool_t		inv;
    jit_int32_t		reg;
    jit_word_t		lo, hi;
    if (can_sign_extend_short_p(i0))
	LHA(r0, _R0_REGNO, i0);
    else {
	hi = (i0 >> 16) + ((jit_uint16_t)i0 >> 15);
	lo = (jit_int16_t)(i0 - (hi << 16));
	reg = jit_get_reg(jit_class_gpr);
	if ((inv = reg == _R0))		reg = jit_get_reg(jit_class_gpr);
	LIS(rn(reg), hi);
	LHA(r0, rn(reg), lo);
	jit_unget_reg(reg);
	if (inv)			jit_unget_reg(_R0);
    }
}

static void
_ldxr_s(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_int32_t r2)
{
    jit_int32_t		reg;
    if (r1 == _R0_REGNO) {
	if (r2 != _R0_REGNO)
	    LHAX(r0, r2, r1);
	else {
	    reg = jit_get_reg(jit_class_gpr);
	    movr(rn(reg), r1);
	    LHAX(r0, rn(reg), r2);
	    jit_unget_reg(reg);
	}
    }
    else
	LHAX(r0, r1, r2);
}

static void
_ldxi_s(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_word_t i0)
{
    jit_int32_t		reg;
    if (i0 == 0)
	ldr_s(r0, r1);
    else if (can_sign_extend_short_p(i0)) {
	if (r1 == _R0_REGNO) {
	    reg = jit_get_reg(jit_class_gpr);
	    movr(rn(reg), r1);
	    LHA(r0, rn(reg), i0);
	    jit_unget_reg(reg);
	}
	else
	    LHA(r0, r1, i0);
    }
    else {
	reg = jit_get_reg(jit_class_gpr);
	movi(rn(reg), i0);
	ldxr_s(r0, r1, rn(reg));
	jit_unget_reg(reg);
    }
}

static void
_ldi_us(jit_state_t *_jit, jit_int32_t r0, jit_word_t i0)
{
    jit_bool_t		inv;
    jit_int32_t		reg;
    jit_word_t		lo, hi;
    if (can_sign_extend_short_p(i0))
	LHZ(r0, _R0_REGNO, i0);
    else {
	hi = (i0 >> 16) + ((jit_uint16_t)i0 >> 15);
	lo = (jit_int16_t)(i0 - (hi << 16));
	reg = jit_get_reg(jit_class_gpr);
	if ((inv = reg == _R0))		reg = jit_get_reg(jit_class_gpr);
	LIS(rn(reg), hi);
	LHZ(r0, rn(reg), lo);
	jit_unget_reg(reg);
	if (inv)			jit_unget_reg(_R0);
    }
}

static void
_ldxr_us(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_int32_t r2)
{
    jit_int32_t		reg;
    if (r1 == _R0_REGNO) {
	if (r2 != _R0_REGNO)
	    LHZX(r0, r2, r1);
	else {
	    reg = jit_get_reg(jit_class_gpr);
	    movr(rn(reg), r1);
	    LHZX(r0, rn(reg), r2);
	    jit_unget_reg(reg);
	}
    }
    else
	LHZX(r0, r1, r2);
}

static void
_ldxi_us(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_word_t i0)
{
    jit_int32_t		reg;
    if (i0 == 0)
	ldr_us(r0, r1);
    else if (can_sign_extend_short_p(i0)) {
	if (r1 == _R0_REGNO) {
	    reg = jit_get_reg(jit_class_gpr);
	    movr(rn(reg), r1);
	    LHZ(r0, rn(reg), i0);
	    jit_unget_reg(reg);
	}
	else
	    LHZ(r0, r1, i0);
    }
    else {
	reg = jit_get_reg(jit_class_gpr);
	movi(rn(reg), i0);
	ldxr_us(r0, r1, rn(reg));
	jit_unget_reg(reg);
    }
}

static void
_ldi_i(jit_state_t *_jit, jit_int32_t r0, jit_word_t i0)
{
    jit_bool_t		inv;
    jit_int32_t		reg;
    jit_word_t		lo, hi;
    if (can_sign_extend_short_p(i0))
	LWZ(r0, _R0_REGNO, i0);
    else {
	hi = (i0 >> 16) + ((jit_uint16_t)i0 >> 15);
	lo = (jit_int16_t)(i0 - (hi << 16));
	reg = jit_get_reg(jit_class_gpr);
	if ((inv = reg == _R0))		reg = jit_get_reg(jit_class_gpr);
	LIS(rn(reg), hi);
	LWZ(r0, rn(reg), lo);
	jit_unget_reg(reg);
	if (inv)			jit_unget_reg(_R0);
    }
}

static void
_ldxr_i(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_int32_t r2)
{
    jit_int32_t		reg;
    if (r1 == _R0_REGNO) {
	if (r2 != _R0_REGNO)
	    LWZX(r0, r2, r1);
	else {
	    reg = jit_get_reg(jit_class_gpr);
	    movr(rn(reg), r1);
	    LWZX(r0, rn(reg), r2);
	    jit_unget_reg(reg);
	}
    }
    else
	LWZX(r0, r1, r2);
}

static void
_ldxi_i(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_word_t i0)
{
    jit_int32_t		reg;
    if (i0 == 0)
	ldr_i(r0, r1);
    else if (can_sign_extend_short_p(i0)) {
	if (r1 == _R0_REGNO) {
	    reg = jit_get_reg(jit_class_gpr);
	    movr(rn(reg), r1);
	    LWZ(r0, rn(reg), i0);
	    jit_unget_reg(reg);
	}
	else
	    LWZ(r0, r1, i0);
    }
    else {
	reg = jit_get_reg(jit_class_gpr);
	movi(rn(reg), i0);
	ldxr_i(r0, r1, rn(reg));
	jit_unget_reg(reg);
    }
}

static void
_sti_c(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0)
{
    jit_bool_t		inv;
    jit_int32_t		reg;
    jit_word_t		lo, hi;
    if (can_sign_extend_short_p(i0))
	STB(r0, _R0_REGNO, i0);
    else {
	hi = (i0 >> 16) + ((jit_uint16_t)i0 >> 15);
	lo = (jit_int16_t)(i0 - (hi << 16));
	reg = jit_get_reg(jit_class_gpr);
	if ((inv = reg == _R0))		reg = jit_get_reg(jit_class_gpr);
	LIS(rn(reg), hi);
	STB(r0, rn(reg), lo);
	jit_unget_reg(reg);
	if (inv)			jit_unget_reg(_R0);
    }
}

static void
_stxr_c(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_int32_t r2)
{
    jit_int32_t		reg;
    if (r0 == _R0_REGNO) {
	if (r1 != _R0_REGNO)
	    STBX(r2, r1, r0);
	else {
	    reg = jit_get_reg(jit_class_gpr);
	    movr(rn(reg), r0);
	    STBX(r2, rn(reg), r1);
	    jit_unget_reg(reg);
	}
    }
    else
	STBX(r2, r0, r1);
}

static void
_stxi_c(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_int32_t r1)
{
    jit_int32_t		reg;
    if (i0 == 0)
	str_c(r0, r1);
    else if (can_sign_extend_short_p(i0)) {
	if (r0 == _R0_REGNO) {
	    reg = jit_get_reg(jit_class_gpr);
	    movr(rn(reg), i0);
	    STB(r1, rn(reg), i0);
	    jit_unget_reg(reg);
	}
	else
	    STB(r1, r0, i0);
    }
    else {
	reg = jit_get_reg(jit_class_gpr);
	movi(rn(reg), i0);
	stxr_c(rn(reg), r0, r1);
	jit_unget_reg(reg);
    }
}

static void
_sti_s(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0)
{
    jit_bool_t		inv;
    jit_int32_t		reg;
    jit_word_t		lo, hi;
    if (can_sign_extend_short_p(i0))
	STH(r0, _R0_REGNO, i0);
    else {
	hi = (i0 >> 16) + ((jit_uint16_t)i0 >> 15);
	lo = (jit_int16_t)(i0 - (hi << 16));
	reg = jit_get_reg(jit_class_gpr);
	if ((inv = reg == _R0))		reg = jit_get_reg(jit_class_gpr);
	LIS(rn(reg), hi);
	STH(r0, rn(reg), lo);
	jit_unget_reg(reg);
	if (inv)			jit_unget_reg(_R0);
    }
}

static void
_stxr_s(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_int32_t r2)
{
    jit_int32_t		reg;
    if (r0 == _R0_REGNO) {
	if (r1 != _R0_REGNO)
	    STHX(r2, r1, r0);
	else {
	    reg = jit_get_reg(jit_class_gpr);
	    movr(rn(reg), r0);
	    STHX(r2, rn(reg), r1);
	    jit_unget_reg(reg);
	}
    }
    else
	STHX(r2, r0, r1);
}

static void
_stxi_s(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_int32_t r1)
{
    jit_int32_t		reg;
    if (i0 == 0)
	str_s(r0, r1);
    else if (can_sign_extend_short_p(i0)) {
	if (r0 == _R0_REGNO) {
	    reg = jit_get_reg(jit_class_gpr);
	    movr(rn(reg), i0);
	    STH(r1, rn(reg), i0);
	    jit_unget_reg(reg);
	}
	else
	    STH(r1, r0, i0);
    }
    else {
	reg = jit_get_reg(jit_class_gpr);
	movi(rn(reg), i0);
	stxr_s(rn(reg), r0, r1);
	jit_unget_reg(reg);
    }
}

static void
_sti_i(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0)
{
    jit_bool_t		inv;
    jit_int32_t		reg;
    jit_word_t		lo, hi;
    if (can_sign_extend_short_p(i0))
	STW(r0, _R0_REGNO, i0);
    else {
	hi = (i0 >> 16) + ((jit_uint16_t)i0 >> 15);
	lo = (jit_int16_t)(i0 - (hi << 16));
	reg = jit_get_reg(jit_class_gpr);
	if ((inv = reg == _R0))		reg = jit_get_reg(jit_class_gpr);
	LIS(rn(reg), hi);
	STW(r0, rn(reg), lo);
	jit_unget_reg(reg);
	if (inv)			jit_unget_reg(_R0);
    }
}

static void
_stxr_i(jit_state_t *_jit, jit_int32_t r0, jit_int32_t r1, jit_int32_t r2)
{
    jit_int32_t		reg;
    if (r0 == _R0_REGNO) {
	if (r1 != _R0_REGNO)
	    STWX(r2, r1, r0);
	else {
	    reg = jit_get_reg(jit_class_gpr);
	    movr(rn(reg), r0);
	    STWX(r2, rn(reg), r1);
	    jit_unget_reg(reg);
	}
    }
    else
	STWX(r2, r0, r1);
}

static void
_stxi_i(jit_state_t *_jit, jit_word_t i0, jit_int32_t r0, jit_int32_t r1)
{
    jit_int32_t		reg;
    if (i0 == 0)
	str_i(r0, r1);
    else if (can_sign_extend_short_p(i0)) {
	if (r0 == _R0_REGNO) {
	    reg = jit_get_reg(jit_class_gpr);
	    movr(rn(reg), i0);
	    STW(r1, rn(reg), i0);
	    jit_unget_reg(reg);
	}
	else
	    STW(r1, r0, i0);
    }
    else {
	reg = jit_get_reg(jit_class_gpr);
	movi(rn(reg), i0);
	stxr_i(rn(reg), r0, r1);
	jit_unget_reg(reg);
    }
}

static void
_jmpr(jit_state_t *_jit, jit_int32_t r0)
{
    MTLR(r0);
    BLR();
}

/* pc relative jump */
static jit_word_t
_jmpi(jit_state_t *_jit, jit_word_t i0)
{
    jit_int32_t		reg;
    jit_word_t		w, d;
    reg = jit_get_reg(jit_class_gpr);
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    B(d);
    jit_unget_reg(reg);
    return (w);
}

/* absolute jump */
static jit_word_t
_jmpi_p(jit_state_t *_jit, jit_word_t i0)
{
    jit_word_t		w;
    jit_int32_t		reg;
    reg = jit_get_reg(jit_class_gpr);
    w = movi_p(rn(reg), i0);
    jmpr(rn(reg));
    jit_unget_reg(reg);
    return (w);
}

static void
_callr(jit_state_t *_jit, jit_int32_t r0)
{
    MTCTR(r0);
    BCTRL();
}

/* assume fixed address or reachable address */
static jit_word_t
_calli(jit_state_t *_jit, jit_word_t i0)
{
    jit_word_t		w, d;
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    if (can_sign_extend_jump_p(d))
	BL(d);
    else
	w = calli_p(i0);
    return (w);
}

/* absolute jump */
static jit_word_t
_calli_p(jit_state_t *_jit, jit_word_t i0)
{
    jit_word_t		w;
    jit_int32_t		reg;
    reg = jit_get_reg(jit_class_gpr);
    w = movi_p(rn(reg), i0);
    callr(rn(reg));
    jit_unget_reg(reg);
    return (w);
}

static void
_prolog(jit_state_t *_jit, jit_node_t *node)
{
    unsigned long	 regno;
    jit_function_t	*function;
    jit_pointer_t	*functions;

    functions = _jit->functions->v.obj;
    function = functions[node->u.w];
    subi(_SP_REGNO, _SP_REGNO, stack_framesize);
    /* return address */
    MFLR(_R0_REGNO);
    stxi(0, _SP_REGNO, _R0_REGNO);

    /* save any clobbered  callee save fpr register */
    /* FIXME actually, no "clean" interface to use these registers */
    for (regno = _F31; regno >= _F14; regno--) {
	if (jit_regset_tstbit(function->regset, regno))
	    stxi_d(stack_framesize - rn(regno) * 8, _SP_REGNO, regno);
    }
    /* save any clobbered callee save gpr register */
    regno = jit_regset_scan1(function->regset, _R14);
    if (regno == ULONG_MAX || regno > _R31)
	regno = _R31;	/* aka _FP_REGNO */
    STMW(regno, _SP_REGNO, rn(regno) * 4 + 8);
    movr(_FP_REGNO, _SP_REGNO);
    /* alloca and/or space for excess parameters */
    subi(_SP_REGNO, _SP_REGNO, function->stack);
}

static void
_epilog(jit_state_t *_jit, jit_node_t *node)
{
    unsigned long	 regno;
    jit_function_t	*function;
    jit_pointer_t	*functions;

    functions = _jit->functions->v.obj;
    function = functions[node->w.w];
    movr(_SP_REGNO, _FP_REGNO);
    for (regno = _F31; regno >= _F14; regno--) {
	if (jit_regset_tstbit(function->regset, regno))
	    ldxi_d(regno, _SP_REGNO, stack_framesize - rn(regno) * 8);
    }
    regno = jit_regset_scan1(function->regset, _R14);
    if (regno == ULONG_MAX || regno > _R31)
	regno = _R31;	/* aka _FP_REGNO */
    LMW(rn(regno), _SP_REGNO, regno * 4 + 8);
    ldxi(_R0_REGNO, _SP_REGNO, 0);
    addi(_SP_REGNO, _SP_REGNO, stack_framesize);
    MTLR(_R0_REGNO);
    BLR();
}

static void
_patch_at(jit_state_t *_jit, jit_word_t instr, jit_word_t label)
{
    jit_word_t		 d;
    union {
	jit_int32_t	*i;
	jit_word_t	 w;
    } u;
    u.w = instr;
    switch ((u.i[0] & 0xfc000000) >> 26) {
	case 16:					/* BCx */
	    d = label - instr;
	    assert(!(d & 3));
	    if (!can_sign_extend_short_p(d)) {
		/* use absolute address */
		assert(can_sign_extend_short_p(label));
		d |= 2;
	    }
	    u.i[0] = (u.i[0] & ~0xfffd) | (d & 0xfffe);
	    break;
	case 18:					/* Bx */
	    d = label - instr;
	    assert(!(d & 3));
	    if (!can_sign_extend_jump_p(d)) {
		/* use absolute address */
		assert(can_sign_extend_jump_p(label));
		d |= 2;
	    }
	    u.i[0] = (u.i[0] & ~0x3fffffd) | (d & 0x3fffffe);
	    break;
	case 15:					/* LI */
	    assert(!(u.i[0] & 0x1f0000));
	    u.i[0] = (u.i[0] & ~0xffff) | ((label >> 16) & 0xffff);
	    assert((u.i[1] & 0xfc000000) >> 26 == 24);	/* ORI */
	    assert(((u.i[1] >> 16) & 0x1f) == ((u.i[1] >> 21) & 0x1f));
	    u.i[1] = (u.i[1] & ~0xffff) | (label & 0xffff);
	    break;
	default:
	    assert(!"unhandled branch opcode");
    }
}
#endif