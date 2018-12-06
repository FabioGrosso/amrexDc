#ifndef _slope_cpp_
#define _slope_cpp_

#include <AmrCoreAdv_F.H>
#include <AMReX_CudaDevice.H>

using namespace amrex;

void slopex2(Box const& bx,
            const FArrayBox &qfab,
            FArrayBox &dqfab)
{
     // Find 2nd order slope
     AMREX_LAUNCH_DEVICE_LAMBDA(bx, tbx,
     {
         const auto len = length(tbx);
         const auto lo  = lbound(tbx);
         const auto q   =  qfab.view(lo);
         const auto dq  = dqfab.view(lo);

         for         (int k = 0; k < len.z; ++k) {
             for     (int j = 0; j < len.y; ++j) {
                 for (int i = 0; i < len.x; ++i) {
                     Real dlft = q(i,j,k) - q(i-1,j,k);
                     Real drgt = q(i+1,j,k) - q(i,j,k);
                     Real dcen = 0.5*(dlft+drgt);
                     Real dsgn = copysign(1.0, dcen);
                     Real dslop = 2.0 * ((std::abs(dlft) < std::abs(drgt)) ?
                                          std::abs(dlft) : std::abs(drgt));
                     Real dlim = (dlft*drgt >= 0.0) ? dslop : 0.0;
                     dq(i,j,k) = dsgn*std::min(dlim, std::abs(dcen));
                 }
             }
         }
     });
}

void slopex4(Box const& bx,
             const FArrayBox &qfab,
             const FArrayBox &dqfab,
             FArrayBox &dq4fab)
{
     // Calc 4th order slope from 2nd order slope
     AMREX_LAUNCH_DEVICE_LAMBDA(bx, tbx,
     {
         const auto len = length(tbx);
         const auto lo  = lbound(tbx);
         const auto q   =   qfab.view(lo);
         const auto dq  =  dqfab.view(lo);
         const auto dq4 = dq4fab.view(lo);

         for         (int k = 0; k < len.z; ++k) {
             for     (int j = 0; j < len.y; ++j) {
                 for (int i = 0; i < len.x; ++i) {
                     Real dlft = q(i,j,k) - q(i-1,j,k);
                     Real drgt = q(i+1,j,k) - q(i,j,k);
                     Real dcen = 0.5*(dlft+drgt);
                     Real dsgn = copysign(1.0, dcen);
                     Real dslop = 2.0 * ((std::abs(dlft) < std::abs(drgt)) ?
                                          std::abs(dlft) : std::abs(drgt));
                     Real dlim = (dlft*drgt >= 0.0) ? dslop : 0.0;
                     Real dq1 = 4.0/3.0*dcen - (1.0/6.0)*(dq(i+1,j,k) + dq(i-1,j,k));
                     dq4(i,j,k) = dsgn*std::min(dlim, std::abs(dq1));
                 }
             }
         }
     });
}

// ***********************************************************

void slopey2(Box const& bx,
            const FArrayBox &qfab,
            FArrayBox &dqfab)
{
     // Find 2nd order slope
     AMREX_LAUNCH_DEVICE_LAMBDA(bx, tbx,
     {
         const auto len = length(tbx);
         const auto lo  = lbound(tbx);
         const auto q   =  qfab.view(lo);
         const auto dq  = dqfab.view(lo);

         for         (int k = 0; k < len.z; ++k) {
             for     (int j = 0; j < len.y; ++j) {
                 for (int i = 0; i < len.x; ++i) {
                     Real dlft = q(i,j,k) - q(i,j-1,k);
                     Real drgt = q(i,j+1,k) - q(i,j,k);
                     Real dcen = 0.5*(dlft+drgt);
                     Real dsgn = copysign(1.0, dcen);
                     Real dslop = 2.0 * ((std::abs(dlft) < std::abs(drgt)) ?
                                          std::abs(dlft) : std::abs(drgt));
                     Real dlim = (dlft*drgt >= 0.0) ? dslop : 0.0;
                     dq(i,j,k) = dsgn*std::min(dlim, std::abs(dcen));
                 }
             }
         }
     });
}

void slopey4(Box const& bx,
             const FArrayBox &qfab,
             const FArrayBox &dqfab,
             FArrayBox &dq4fab)
{
     // Calc 4th order slope from 2nd order slope
     AMREX_LAUNCH_DEVICE_LAMBDA(bx, tbx,
     {
         const auto len = length(tbx);
         const auto lo  = lbound(tbx);
         const auto q   =   qfab.view(lo);
         const auto dq  =  dqfab.view(lo);
         const auto dq4 = dq4fab.view(lo);

         for         (int k = 0; k < len.z; ++k) {
             for     (int j = 0; j < len.y; ++j) {
                 for (int i = 0; i < len.x; ++i) {
                     Real dlft = q(i,j,k) - q(i,j-1,k);
                     Real drgt = q(i,j+1,k) - q(i,j,k);
                     Real dcen = 0.5*(dlft+drgt);
                     Real dsgn = copysign(1.0, dcen);
                     Real dslop = 2.0 * ((std::abs(dlft) < std::abs(drgt)) ?
                                          std::abs(dlft) : std::abs(drgt));
                     Real dlim = (dlft*drgt >= 0.0) ? dslop : 0.0;
                     Real dq1 = 4.0/3.0*dcen - (1.0/6.0)*(dq(i,j+1,k) + dq(i,j-1,k));
                     dq4(i,j,k) = dsgn*std::min(dlim, std::abs(dq1));
                 }
             }
         }
     });
}

// ***********************************************************

void slopez2(Box const& bx,
            const FArrayBox &qfab,
            FArrayBox &dqfab)
{
     // Find 2nd order slope
     AMREX_LAUNCH_DEVICE_LAMBDA(bx, tbx,
     {
         const auto len = length(tbx);
         const auto lo  = lbound(tbx);
         const auto q   =  qfab.view(lo);
         const auto dq  = dqfab.view(lo);

         for         (int k = 0; k < len.z; ++k) {
             for     (int j = 0; j < len.y; ++j) {
                 for (int i = 0; i < len.x; ++i) {
                     Real dlft = q(i,j,k) - q(i,j,k-1);
                     Real drgt = q(i,j,k+1) - q(i,j,k);
                     Real dcen = 0.5*(dlft+drgt);
                     Real dsgn = copysign(1.0, dcen);
                     Real dslop = 2.0 * ((std::abs(dlft) < std::abs(drgt)) ?
                                          std::abs(dlft) : std::abs(drgt));
                     Real dlim = (dlft*drgt >= 0.0) ? dslop : 0.0;
                     dq(i,j,k) = dsgn*std::min(dlim, std::abs(dcen));
                 }
             }
         }
     });
}

void slopez4(Box const& bx,
             const FArrayBox &qfab,
             const FArrayBox &dqfab,
             FArrayBox &dq4fab)
{
     // Calc 4th order slope from 2nd order slope
     AMREX_LAUNCH_DEVICE_LAMBDA(bx, tbx,
     {
         const auto len = length(tbx);
         const auto lo  = lbound(tbx);
         const auto q   =   qfab.view(lo);
         const auto dq  =  dqfab.view(lo);
         const auto dq4 = dq4fab.view(lo);

         for         (int k = 0; k < len.z; ++k) {
             for     (int j = 0; j < len.y; ++j) {
                 for (int i = 0; i < len.x; ++i) {
                     Real dlft = q(i,j,k) - q(i,j,k-1);
                     Real drgt = q(i,j,k+1) - q(i,j,k);
                     Real dcen = 0.5*(dlft+drgt);
                     Real dsgn = copysign(1.0, dcen);
                     Real dslop = 2.0 * ((std::abs(dlft) < std::abs(drgt)) ?
                                          std::abs(dlft) : std::abs(drgt));
                     Real dlim = (dlft*drgt >= 0.0) ? dslop : 0.0;
                     Real dq1 = 4.0/3.0*dcen - (1.0/6.0)*(dq(i,j,k+1) + dq(i,j,k-1));
                     dq4(i,j,k) = dsgn*std::min(dlim, std::abs(dq1));
                 }
             }
         }
     });
}

#endif