--- ../../../CMS32L051.h	2020-07-30 14:14:33.664967400 +0800
+++ CMS32L051.h	2020-07-30 14:16:22.182505300 +0800
@@ -66,13 +66,26 @@
   TM01H_IRQn                =   5,              /*!< 5  TM40 channel 1(higher 8 bit) interrupt request                         */
   KEY_IRQn                  =   6,              /*!< 6  KEY return interrupt request                                           */
   ST2_IRQn                  =   7,              /*!< 7  UART2 transmission transfer end or buffer empty                        */
+  SPI20_IRQn                =   7,              /*!< 7  SPI20 transfer end or buffer empty                                     */
+  IIC20_IRQn                =   7,              /*!< 7  IIC20 transfer end                                                     */
   SR2_IRQn                  =   8,              /*!< 8  UART2 rerception transfer                                              */
+  SPI21_IRQn                =   8,              /*!< 8  SPI21 transfer end or buffer empty                                     */
+  IIC21_IRQn                =   8,              /*!< 8  IIC21 transfer end                                                     */
   SRE2_IRQn                 =   9,              /*!< 9  UART2 rerception communication error occurrence                        */
   ST0_IRQn                  =  10,              /*!< 10 UART0 transmission transfer end or buffer empty                        */
+  SPI00_IRQn                =  10,              /*!< 10 SPI00 transfer end or buffer empty                                     */
+  IIC00_IRQn                =  10,              /*!< 10 IIC00 transfer end                                                     */
   SR0_IRQn                  =  11,              /*!< 11 UART0 rerception transfer                                              */
+  SPI01_IRQn                =  11,              /*!< 11 SPI01 transfer end or buffer empty                                     */
+  IIC01_IRQn                =  11,              /*!< 11 IIC01 transfer end                                                     */
   SRE0_IRQn                 =  12,              /*!< 12 UART0 rerception communication error occurrence                        */
   ST1_IRQn                  =  13,              /*!< 13 UART1 transmission transfer end or buffer empty                        */
+  SPI10_IRQn                =  13,              /*!< 13 SPI10 transfer end or buffer empty                                     */
+  IIC10_IRQn                =  13,              /*!< 13 IIC10 transfer end                                                     */
+  SPI_IRQn                  =  13,              /*!< 13 SPI   transfer end                                                     */
   SR1_IRQn                  =  14,              /*!< 14 UART1 rerception transfer                                              */
+  SPI11_IRQn                =  14,              /*!< 14 SPI11 transfer end or buffer empty                                     */
+  IIC11_IRQn                =  14,              /*!< 14 IIC11 transfer end                                                     */
   SRE1_IRQn                 =  15,              /*!< 15 UART1 rerception communication error occurrence                        */
   IICA_IRQn                 =  16,              /*!< 16 IICA interrupt request                                                 */
   TM00_IRQn                 =  17,              /*!< 17 TM40 channel 0 interrupt request                                       */
