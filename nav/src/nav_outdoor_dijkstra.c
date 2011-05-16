/*

    @file:  dijk.c
    
    @author: Qiushi Wang & Amanpreet Kaur

    @date:   Apr 6th,2011
    
    @brief: load map info, set start point and end point,then calculate best path.

*/
#include "nav_outdoor_dijkstra.h"

/* define the nodes */
struct point* init_map()
{
	struct point *p1 = malloc(sizeof(struct point));
	p1 [0].name = 1;    
	p1 [0].lat = 57.7068;
	p1 [0].lon = 11.9374;

	p1 = realloc(p1,2*sizeof(struct point));
	p1 [1].name = 2;    
	p1 [1].lat = 57.7064;
	p1 [1].lon = 11.9371;

	p1 = realloc(p1,3*sizeof(struct point));
	p1 [2].name = 3;    
	p1 [2].lat = 57.70622;
	p1 [2].lon = 11.93784;

	p1 = realloc(p1,4*sizeof(struct point));
	p1 [3].name = 4;    
	p1 [3].lat = 57.70581;
	p1 [3].lon = 11.93749;

	p1 = realloc(p1,5*sizeof(struct point));
	p1 [4].name = 5;    
	p1 [4].lat = 57.70597;
	p1 [4].lon = 11.93672;

	p1 = realloc(p1,6*sizeof(struct point));
	p1 [5].name = 6;    
	p1 [5].lat = 57.70619;
	p1 [5].lon = 11.93589;

	p1 = realloc(p1,7*sizeof(struct point));
	p1 [6].name = 7;    
	p1 [6].lat = 57.70636;
	p1 [6].lon = 11.93526;

	p1 = realloc(p1,8*sizeof(struct point));
	p1 [7].name = 8;    
	p1 [7].lat = 57.70622;
	p1 [7].lon = 11.93626;

	p1 = realloc(p1,9*sizeof(struct point));
	p1 [8].name = 9;    
	p1 [8].lat = 57.70679;
	p1 [8].lon = 11.93568;

	p1 = realloc(p1,10*sizeof(struct point));
	p1 [9].name = 10;   
	p1 [9].lat = 57.70707;
	p1 [9].lon = 11.93670;

	p1 = realloc(p1,11*sizeof(struct point));
	p1 [10].name = 11;  
	p1 [10].lat = 57.70723;
	p1 [10].lon = 11.93612;

	p1 = realloc(p1,12*sizeof(struct point));
	p1 [11].name = 12;  
	p1 [11].lat = 57.70545;
	p1 [11].lon = 11.93424;

	p1 = realloc(p1,13*sizeof(struct point));
	p1 [12].name = 13;  
	p1 [12].lat = 57.70502;
	p1 [12].lon = 11.93583;
    
	p1 = realloc(p1,14*sizeof(struct point));
	p1 [13].name = -1;  
	p1 [13].lat = 0;
	p1 [13].lon = 0;

	return p1;
}



/* make node related to others*/
struct link* init_link(struct link* link, struct point* p)
{
    link = add_link(1,2,calc_dist(p [0],p [1]),link);
    link = add_link(1,10,calc_dist(p [0],p [9]),link);

    link = add_link(2,1,calc_dist(p [1],p [0]),link);
    link = add_link(2,3,calc_dist(p [1],p [2]),link);
    link = add_link(2,8,calc_dist(p [1],p [7]),link);
    link = add_link(2,5,calc_dist(p [1],p [4]),link);

    link = add_link(3,2,calc_dist(p [2],p [1]),link);
    link = add_link(3,4,calc_dist(p [2],p [3]),link);

    link = add_link(4,3,calc_dist(p [3],p [2]),link);
    link = add_link(4,5,calc_dist(p [3],p [4]),link);

    link = add_link(5,2,calc_dist(p [4],p [1]),link);
    link = add_link(5,4,calc_dist(p [4],p [3]),link);
    link = add_link(5,6,calc_dist(p [4],p [5]),link);
    link = add_link(5,13,calc_dist(p [4],p [12]),link);

    link = add_link(6,5,calc_dist(p [5],p [4]),link);
    link = add_link(6,7,calc_dist(p [5],p [6]),link);
    link = add_link(6,8,calc_dist(p [5],p [7]),link);

    link = add_link(7,6,calc_dist(p [6],p [5]),link);
    link = add_link(7,9,calc_dist(p [6],p [8]),link);
    link = add_link(7,12,calc_dist(p [6],p [11]),link);


    link = add_link(8,2,calc_dist(p [7],p [1]),link);
    link = add_link(8,6,calc_dist(p [7],p [5]),link);
    link = add_link(8,10,calc_dist(p [7],p [9]),link);
    link = add_link(8,9,calc_dist(p [7],p [8]),link);

    link = add_link(9,8,calc_dist(p [8],p [7]),link);
    link = add_link(9,7,calc_dist(p [8],p [6]),link);
    link = add_link(9,11,calc_dist(p [8],p [10]),link);

    link = add_link(10,11,calc_dist(p [9],p [10]),link);
    link = add_link(10,8,calc_dist(p [9],p [7]),link);
    link = add_link(10,1,calc_dist(p [9],p [0]),link);


    link = add_link(11,10,calc_dist(p [10],p [9]),link);
    link = add_link(11,9,calc_dist(p [10],p [8]),link);

    link = add_link(12,7,calc_dist(p [11],p [6]),link);
    link = add_link(12,13,calc_dist(p [11],p [12]),link);

    link = add_link(13,5,calc_dist(p [12],p [4]),link);
    link = add_link(13,12,calc_dist(p [12],p [11]),link);

    link = add_link(0,0,0,link);

    return link; 
}



struct link* remove_from_list(struct link* this,struct link* list)
{
    struct link* lt = list;
    struct link* next = NULL;
    struct link* nt = NULL;

    while(lt!=NULL)
    {
    if(next==NULL){
    
        if(lt->to == this->to){
        nt = lt->last;      

        free(lt);

        lt = nt;
        
        }else{
        next = lt;      
        lt = lt->last;
        }
    
    }else{/*if (next!=NULL)*/
    
        if(lt->to == this->to){
        next->last = lt->last;
        
        free(lt);
    
        lt = next->last;

        }else{
        next = lt;
        lt = lt->last;              
        }
    }
        
    }/*while*/
    return list;
}




/* to waiting list */
struct link* move_to_wl(struct link* curr,struct link* lk,struct link* wl)
{
    struct link *_lk = lk;  
    struct link *head = NULL;
    struct link *next = NULL;

    while(_lk != NULL)
    {
        if(curr->to == _lk->from)
        {
            head = _lk->last;

            wl = add_link(_lk->from,_lk->to,_lk->distance + curr->distance,wl);

//          printf("new one added: %d->%d :%f\n",_lk->from,_lk->to,_lk->distance + curr->distance);

            if(next!=NULL)
            {
            next->last = head;          
            }
            free(_lk);
            _lk = head;         
        }else
        {
        next = _lk;
        _lk = _lk->last;
        }                   
    }

    return wl;                                                  
}





/* cancel some links in waiting list */
struct link* remove_from_wl(struct link* next,struct link* wl)
{
    struct link* this = wl;

    while(this!=NULL)
    {
        if(this->to == next->to)
        {
            this->from = 0;
        }

        this = this->last;
    }

return wl;
}




/* in waiting list, find the point which can be next one */
struct link* select_next(struct link* waiting_list)
{
    struct link* wl = waiting_list;

    struct link* curr = waiting_list;

    while(wl != NULL)
    {
        if(wl->from != 0)
        {       
            if(curr->distance >= wl->distance)
            curr = wl;
        }

        wl = wl->last;
    }
    return curr;    
}




/* each selected link will be stored, used to extract the path */
struct link* store_selected(struct link* new,struct link* collection)
{
    collection = add_link(new->from,new->to,new->distance,collection);
    return collection;
}



/* get the path */
struct trac* get_path(struct link* collection,char startp,char endp)
{
    struct link* col = collection;
    struct link* curr = collection->last;
<<<<<<< HEAD
    struct link* head = NULL;
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b

    struct trac *path = NULL;
    struct trac *head_ = NULL;

    path = malloc(sizeof(struct trac));
    path->p = endp;
    path->last = NULL;
    head_ = path;

    while(curr!=NULL)
    {
        if(col->from == curr->to)
        {   
            path = malloc(sizeof(struct trac));

            path->p = col->from;
            path->last = head_;
            head_ = path;           

            col = curr;
            curr = col->last;

        }else
        {
            curr = curr->last;
        }
    }
    path = malloc(sizeof(struct trac));
    path->p = startp;           
    path->last = head_;

    return path;
}




struct link* add_link(char from, char to, double distance,struct link* last)
{
    struct link* this = malloc(sizeof(struct link));
    this->from = from;
    this->to = to;
    this->distance = distance;

    this->last = last;
    return this;
}



void deallocate_link(struct link *list)
{
    struct link *head = NULL,*curr = NULL;
    
    curr = list;

    while(curr != NULL)
    {
        head = curr->last;
        free(curr);
        curr = head;    
    }   

}





void deallocate_trac(struct trac *list)
{
    struct trac *head = NULL,*curr = NULL;
    curr = list;

    while(curr != NULL)
    {
        head = curr->last;
        free(curr);
        curr = head;    
    }   
}


        


struct trac* calculate(char startp,char endp,struct link* lk)
{
    if(startp == endp)
    {
    printf("i think you are there   --!  \n");
    return NULL;
    }

    struct link *wl,*next,*curr,*collection;                    

    struct trac* sb = NULL;
                        
    wl = next = curr = collection = NULL;
    
    struct link* start = malloc(sizeof(struct link));                       
    start->from = startp;start->to = startp;start->distance = 0;start->last = NULL;

    struct link* end = malloc(sizeof(struct link));                     
    end->from = endp;end->to = endp;end->distance = 0;end->last = NULL;

    curr = next = start;
    while(curr->to != end->from)                
    {
        lk = remove_from_list(curr,lk);         
        wl = move_to_wl(curr,lk,wl);
        next = select_next(wl);
        
        collection = store_selected(next,collection);

        curr = next;

        remove_from_wl(curr,wl);
    }

    sb = get_path(collection,startp,endp);

    free(start);

    free(end);

    deallocate_link(wl);

    deallocate_link(collection);

    return sb;
}



