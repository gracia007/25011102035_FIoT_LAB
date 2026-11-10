else if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12)==GPIO_PIN_SET) {
			if(pressed!=0 && release_debounce==0) {
				debounce= HAL_GetTick();
				press_release= HAL_GetTick();
				release_debounce=1;
			}	
			if(release_debounce==1 && HAL_GetTick()-debounce>=10 && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12)==GPIO_PIN_SET) {
					pressed=0;
					release_debounce=0;
				
				if(pressed==0 && (press_release-press_start)<1000) {
					if(isBlinking==0) HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_10);
					else {
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
						isBlinking=0;
					}
			}
			else if(pressed==0 && (press_release-press_start)>=1000){
				if(isBlinking==0) {
					isBlinking=1;
					HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_10);
					blinking_start=HAL_GetTick();
				}
			}
		}	
			
}
if(isBlinking==1) {
	if((HAL_GetTick()-blinking_start)>=1000) {
		blinking_start=HAL_GetTick();
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_10);
	}
}
		
else if(release_debounce==1 && HAL_GetTick()-debounce>=10 && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12)==GPIO_PIN_RESET) {
	pressed=1;
	release_debounce=0;	
}
