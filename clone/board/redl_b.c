// This program is a part of NITAN MudLIB 
// redl 2013/3
// /clone/board/swing_b.c 
#include <ansi.h>
        
inherit BULLETIN_BOARD; 
        
       void create() 
       { 
                   set_name(RED"无相石"NOR,({"stone"}));
               set("location","/u/redl/workroom");
                 set("board_id","redlstone_b");
                   set("long","“化五尘而自乐，乐自在而化天。”\n");
              setup(); 
              set("capacity", 100); 
              replace_program(BULLETIN_BOARD); 
      } 
       
       
