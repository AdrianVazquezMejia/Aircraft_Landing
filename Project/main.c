#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"		/* RTOS firmware */
#include "task.h"			/* Task */
#include "timers.h"
#include "queue.h"
#include "rsa.h"
#include "candy.h"
//#include "queue.h"
/* Examples */
TaskHandle_t encrypt_handle = NULL;
TaskHandle_t camera_handle = NULL;
TimerHandle_t timer0 = NULL;
static xQueueHandle MatrixQueue = NULL;
typedef struct
{
	bitmap_info_header_t ih;
	pixel_t *bitmap_data;
	/* data */
} QueueData_t;

static void readFromCarmera() 
{
	QueueData_t *data2Queue = malloc(sizeof(QueueData_t));
		static bitmap_info_header_t ih;
		while (1) {
			
			printf("\nStarted Matrrix Task Execution...\n");
			pixel_t *in_bitmap_data = load_bmp("bitmap.bmp", &ih);
			
			if (in_bitmap_data == NULL) {
				fprintf(stderr, "main: BMP image not loaded.\n");
			printf("Error Loading Image\n");
			}
			printf("Info: %d x %d x %d\n", ih.width, ih.height, ih.bitspp);
					pixel_t *out_bitmap_data =
			canny_edge_detection(in_bitmap_data, &ih, 40, 80, 1.0);
			if (out_bitmap_data == NULL) {
				fprintf(stderr, "main: failed canny_edge_detection.\n");
			}
			
			if (save_bmp("out.bmp", &ih, out_bitmap_data)) {
				fprintf(stderr, "main: BMP image not saved.\n");
			//return 1;
			}
	 

			/*
			* In an embedded systems, matrix multiplication would block the CPU for a long time
			* but since this is a PC simulator we must add one additional dummy delay.
			*/
			

			data2Queue->ih = ih;
			data2Queue->bitmap_data = out_bitmap_data;
			xQueueSend(MatrixQueue, data2Queue,(portTickType)portMAX_DELAY);
			vTaskDelay(100);
			free((pixel_t*)in_bitmap_data);
			free((pixel_t*)out_bitmap_data);			
			printf("Finished Matrix Task Execution\n");
	}
}
static void imageEncrypt(){
	long int p,q,n,t,d[262145],en[262145], e[262145];

	long int temp[262145];
	QueueData_t *dataFromQueue = malloc(sizeof(QueueData_t));
	p= 43;
    q = 17;
    n=p*q;
    t=(p-1)*(q-1);
    ce(p,q,t,e,d);
    while (xQueueReceive(MatrixQueue, dataFromQueue,(portTickType)portMAX_DELAY))
	{
		printf("Encrypting\n");
			 encryptImage(dataFromQueue->bitmap_data, dataFromQueue->ih.width, dataFromQueue->ih.height, en, e, temp, n);
			if (save_bmp("out2.bmp", &dataFromQueue->ih, dataFromQueue->bitmap_data)) {
				fprintf(stderr, "main: BMP image not saved.\n");
			}
			printf("\n");
		vTaskDelay(100);
		
	}
}
void vApplicationIdleHook(void);



int main ( void )
{
    printf("Everything OK\n");
	MatrixQueue = xQueueCreate(10, sizeof(QueueData_t));
    xTaskCreate(readFromCarmera, "Camera", 4*1024, NULL, 3, &camera_handle);
	xTaskCreate(imageEncrypt, "Encrypt",2* 1000, NULL, 1, &encrypt_handle);

    vTaskStartScheduler();
    return 0;
}




 void vAssertCalled( unsigned long ulLine, const char * const pcFileName )
{
 	taskENTER_CRITICAL();
	{
        printf("[ASSERT] %s:%lu\n", pcFileName, ulLine);
        fflush(stdout);
	}
	taskEXIT_CRITICAL();
	exit(-1);
} 

void vApplicationIdleHook(void)
{
//	printf("Idle\r\n");
}
