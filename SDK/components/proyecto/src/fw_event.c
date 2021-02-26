/* 
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*        http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include "fw_event.h"

/* ------------------------- Static Variables ------------------------------- */

static SLIST_HEAD(s_min_prio_handlers,fw_event_handler) s_min_prio_handlers = SLIST_HEAD_INITIALIZER(s_min_prio_handlers);
static SLIST_HEAD(s_med_prio_handlers,fw_event_handler) s_med_prio_handlers = SLIST_HEAD_INITIALIZER(s_med_prio_handlers);
static SLIST_HEAD(s_max_prio_handlers,fw_event_handler) s_max_prio_handlers = SLIST_HEAD_INITIALIZER(s_max_prio_handlers);

/* ------------------------- Static Functions ------------------------------- */
static bool event_handler_register(int event_id, fw_event_handler_t event_handler, 
								void* event_handler_arg,int priority){
 	struct fw_event_handler *hand= malloc(sizeof(struct fw_event_handler));
   	if (hand==NULL)
      	return false;
	hand->ev=event_id;
	hand->handler=event_handler;
	hand->handler_args=event_handler_arg;
   	if(priority==1)
   		SLIST_INSERT_HEAD(&s_min_prio_handlers,hand,next);
   	else if(priority==2)
   		SLIST_INSERT_HEAD(&s_med_prio_handlers,hand,next);
   	else if(priority==3)
   		SLIST_INSERT_HEAD(&s_max_prio_handlers,hand,next);
   	return true;
}

static bool event_handler_unregister_min(int event_id, fw_event_handler_t event_handler){
	struct fw_event_handler *hand=NULL;
   	struct fw_event_handler *next_hand=NULL;
   	struct fw_event_handler *aux_hand=NULL;
   	SLIST_FOREACH(hand,&s_min_prio_handlers,next){
	      	if(hand->ev==event_id && hand->handler==event_handler){
	         	aux_hand=hand;
	         	break;
	      	}
	      	else{
	         	next_hand=hand;
	      	}
	   	}
	   	if(aux_hand==NULL)
	      	return false;
	   	if(next_hand==NULL)
	      	SLIST_REMOVE_HEAD(&s_min_prio_handlers, next);
	   	else
	      	SLIST_REMOVE(&s_min_prio_handlers, aux_hand,fw_event_handler,next);
	free(hand);
   	return true;
}

static bool event_handler_unregister_med(int event_id, fw_event_handler_t event_handler){
	struct fw_event_handler *hand=NULL;
   	struct fw_event_handler *next_hand=NULL;
   	struct fw_event_handler *aux_hand=NULL;
   	SLIST_FOREACH(hand,&s_med_prio_handlers,next){
	      	if(hand->ev==event_id && hand->handler==event_handler){
	         	aux_hand=hand;
	         	break;
	      	}
	      	else{
	         	next_hand=hand;
	      	}
	   	}
	   	if(aux_hand==NULL)
	      	return false;
	   	if(next_hand==NULL)
	      	SLIST_REMOVE_HEAD(&s_med_prio_handlers, next);
	   	else
	      	SLIST_REMOVE(&s_med_prio_handlers, aux_hand,fw_event_handler,next);

	free(hand);
   	return true;
}

static bool event_handler_unregister_max(int event_id, fw_event_handler_t event_handler){
	struct fw_event_handler *hand=NULL;
   	struct fw_event_handler *next_hand=NULL;
   	struct fw_event_handler *aux_hand=NULL;
   	SLIST_FOREACH(hand,&s_max_prio_handlers,next){
	      	if(hand->ev==event_id && hand->handler==event_handler){
	         	aux_hand=hand;
	         	break;
	      	}
	      	else{
	         	next_hand=hand;
	      	}
	   	}
	   	if(aux_hand==NULL)
	      	return false;
	   	if(next_hand==NULL)
	      	SLIST_REMOVE_HEAD(&s_max_prio_handlers, next);
	   	else
	      	SLIST_REMOVE(&s_max_prio_handlers, aux_hand,fw_event_handler,next);
	free(hand);
    return true;
}

static bool event_handler_unregister(int event_id, fw_event_handler_t event_handler,
									int priority){
   	if(priority==1){
	   	return event_handler_unregister_min(event_id,event_handler);
	}
	else if(priority==2){
	   	return event_handler_unregister_med(event_id,event_handler);
	}
	else if(priority==3){
	   	return event_handler_unregister_max(event_id,event_handler);
	}
   	else
   		return false;
}
/* ---------------------------- Public API ---------------------------------- */


bool fw_event_handler_register(int event_id, fw_event_handler_t event_handler, 
								void* event_handler_arg)
{
    return fw_event_med_priority_handler_register(event_id,event_handler,event_handler_arg);
}

bool fw_event_handler_unregister(int event_id, fw_event_handler_t event_handler)
{
    return fw_event_med_priority_handler_unregister(event_id,event_handler);
}

bool fw_event_post(int event_id, void* event_args)
{
    if(event_id<0)
      return false;
   struct fw_event_handler *hand=NULL;
   SLIST_FOREACH(hand,&s_max_prio_handlers,next){
      if(hand->ev==event_id)
         hand->handler(hand->handler_args,event_args);
   }
   SLIST_FOREACH(hand,&s_med_prio_handlers,next){
      if(hand->ev==event_id)
         hand->handler(hand->handler_args,event_args);
   }
   SLIST_FOREACH(hand,&s_min_prio_handlers,next){
      if(hand->ev==event_id)
         hand->handler(hand->handler_args,event_args);
   }
   return true;
}

bool fw_event_max_priority_handler_register(int event_id,fw_event_handler_t event_handler,
											 void* event_handler_arg)
{
    if(event_id<0 || event_handler==NULL)
      return false;
  	return event_handler_register(event_id,event_handler,event_handler_arg,3);
}

bool fw_event_max_priority_handler_unregister(int event_id, fw_event_handler_t event_handler)
{
    if(event_id<0 || event_handler==NULL)
      return false;
  	return event_handler_unregister(event_id,event_handler,3);
}

bool fw_event_med_priority_handler_register(int event_id, fw_event_handler_t event_handler, 
											void* event_handler_arg)
{
    if(event_id<0 || event_handler==NULL)
      return false;
  	return event_handler_register(event_id,event_handler,event_handler_arg,2);
}

bool fw_event_med_priority_handler_unregister(int event_id, fw_event_handler_t event_handler)
{
    if(event_id<0 || event_handler==NULL)
      return false;
  	return event_handler_unregister(event_id,event_handler,2);
}

bool fw_event_min_priority_handler_register(int event_id, fw_event_handler_t event_handler, 
											void* event_handler_arg)
{
    if(event_id<0 || event_handler==NULL)
      	return false;
  	return event_handler_register(event_id,event_handler,event_handler_arg,1);
}

bool fw_event_min_priority_handler_unregister(int event_id, fw_event_handler_t event_handler)
{
    if(event_id<0 || event_handler==NULL)
      return false;
  	return event_handler_unregister(event_id,event_handler,1);
}