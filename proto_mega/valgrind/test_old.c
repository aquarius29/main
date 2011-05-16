int motor(void);
int stab(void);

int main (void)
{
    int i = 0;
    while (i < 10){
        stab();
	    motor();
        i++;
    }
    flush_messages();
    return 1;
}

