#define DEFAULT_OPTION 0
#define Get_Mode() currstate = menu[options()].snum

struct menuitem{
	int snum;
	char* name;
};
extern struct menuitem menu[];

int selectionlist(int length){
	int current = DEFAULT_OPTION;
	int counter = 1;
	int oldcurrent = DEFAULT_OPTION;
	while(1){
		if(a_button()){
			while(a_button())msleep(1);
			return(current);
		}
		if(c_button()){
			while(c_button())msleep(1);
			oldcurrent = current;
			current --;
			counter = 1;
			if(current < 0) current=length-1;
		}
		if(b_button()){
			while(b_button())msleep(1);
			oldcurrent = current;
			current ++;
			counter = 1;
			if (current >= length) current=0;
		}
		if(counter == 1){
			display_printf(0,oldcurrent+1," ");
			display_printf(0,current+1,"*");
			counter = 0;
		}
	}
}
int options(){
	display_clear();
	msleep(10);
	int charlength;
	int result;
	display_printf(0,0,"A Accept|B down|C up\n");
	WAIT(!a_button());
	result = selectionlist(draw_screen());
	display_clear();
	return(result);
}

int draw_screen(){
	int i;
	for(i=0;i<MENUSIZE;i++){
		display_printf(0,i+1,"  %s",menu[i].name);
	}
	return(MENUSIZE);
}
