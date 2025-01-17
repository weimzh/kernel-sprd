/*
 * Copyright (C) 2021-2022 UNISOC Communications Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __QOGIRN6L_MM_DVFS_COFFE_H____
#define __QOGIRN6L_MM_DVFS_COFFE_H____


#define CPP_FREQ_UPD_EN_BYP  0
#define CPP_FREQ_UPD_DELAY_EN  0
#define CPP_FREQ_UPD_HDSK_EN 1
#define CPP_GFREE_WAIT_DELAY 308
#define CPP_SW_TRIG_EN   0
#define CPP_WORK_INDEX_DEF 4
#define CPP_IDLE_INDEX_DEF 0
#define CPP_DFS_EN 1

#define ISP_FREQ_UPD_EN_BYP  0
#define ISP_FREQ_UPD_DELAY_EN  0
#define ISP_FREQ_UPD_HDSK_EN 1
#define ISP_GFREE_WAIT_DELAY 308
#define ISP_SW_TRIG_EN 0
#define ISP_WORK_INDEX_DEF 3
#define ISP_IDLE_INDEX_DEF 0
#define ISP_DFS_EN 1

#define JPEG_FREQ_UPD_EN_BYP  0
#define JPEG_FREQ_UPD_DELAY_EN  0
#define JPEG_FREQ_UPD_HDSK_EN 1
#define JPEG_GFREE_WAIT_DELAY 308
#define JPEG_SW_TRIG_EN 0
#define JPEG_WORK_INDEX_DEF 7
#define JPEG_IDLE_INDEX_DEF 0
#define JPEG_DFS_EN 1

#define DCAM0_1_FREQ_UPD_EN_BYP  0
#define DCAM0_1_FREQ_UPD_DELAY_EN  0
#define DCAM0_1_FREQ_UPD_HDSK_EN 1
#define DCAM0_1_GFREE_WAIT_DELAY 308
#define DCAM0_1_SW_TRIG_EN 0
#define DCAM0_1_WORK_INDEX_DEF 4
#define DCAM0_1_IDLE_INDEX_DEF 2
#define DCAM0_1_DFS_EN 1


#define DCAM0_1_AXI_FREQ_UPD_EN_BYP  0
#define DCAM0_1_AXI_FREQ_UPD_DELAY_EN  0
#define DCAM0_1_AXI_FREQ_UPD_HDSK_EN  1
#define DCAM0_1_AXI_GFREE_WAIT_DELAY 308
#define DCAM0_1_AXI_SW_TRIG_EN 0
#define DCAM0_1_AXI_WORK_INDEX_DEF 4
#define DCAM0_1_AXI_IDLE_INDEX_DEF 2
#define DCAM0_1_AXI_AUTO_TUNE 1

#define DCAM2_3_FREQ_UPD_EN_BYP  0
#define DCAM2_3_FREQ_UPD_DELAY_EN  0
#define DCAM2_3_FREQ_UPD_HDSK_EN 1
#define DCAM2_3_GFREE_WAIT_DELAY 308
#define DCAM2_3_SW_TRIG_EN 0
#define DCAM2_3_WORK_INDEX_DEF 0
#define DCAM2_3_IDLE_INDEX_DEF 0
#define DCAM2_3_DFS_EN 1

#define DCAM2_3_AXI_FREQ_UPD_EN_BYP  0
#define DCAM2_3_AXI_FREQ_UPD_DELAY_EN  0
#define DCAM2_3_AXI_FREQ_UPD_HDSK_EN  1
#define DCAM2_3_AXI_GFREE_WAIT_DELAY 308
#define DCAM2_3_AXI_SW_TRIG_EN 0
#define DCAM2_3_AXI_WORK_INDEX_DEF 0
#define DCAM2_3_AXI_IDLE_INDEX_DEF 0
#define DCAM2_3_AXI_AUTO_TUNE 1


#define DCAM_MTX_FREQ_UPD_EN_BYP  0
#define DCAM_MTX_FREQ_UPD_DELAY_EN  0
#define DCAM_MTX_FREQ_UPD_HDSK_EN  1
#define DCAM_MTX_GFREE_WAIT_DELAY 308
#define DCAM_MTX_SW_TRIG_EN 0
#define DCAM_MTX_WORK_INDEX_DEF 3
#define DCAM_MTX_IDLE_INDEX_DEF 1
#define DCAM_MTX_AUTO_TUNE 1


#define MTX_DATA_FREQ_UPD_EN_BYP  0
#define MTX_DATA_FREQ_UPD_DELAY_EN  0
#define MTX_DATA_FREQ_UPD_HDSK_EN 1
#define MTX_DATA_GFREE_WAIT_DELAY 308
#define MTX_DATA_SW_TRIG_EN 0
#define MTX_DATA_WORK_INDEX_DEF 4
#define MTX_DATA_IDLE_INDEX_DEF 2
#define MM_MTX_AUTO_TUNE 1


#define MMSYS_DVFS_WAIT_UP_WINDOW 0X4D
#define MMSYS_DVFS_WAIT_DOWN_WINDOW 0x9A

#endif /* __QOGIRN6L_MM_DVFS_COFFE_H____ */
