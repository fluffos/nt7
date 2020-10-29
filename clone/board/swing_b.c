// This program is a part of NITAN MudLIB 
// redl 2013/3
// /clone/board/swing_b.c 
#include <ansi.h>
        
inherit BULLETIN_BOARD; 
        
       void create() 
       { 
               set_name(MAG "相思树" NOR, ({ "tree" }) ); 
               set("location", "/d/city/swing"); 
               set("board_id", "swing_b"); 
              set("long", "“相恨不如潮有信，相思始觉海非深。”\n" ); 
              setup(); 
              set("capacity", 100); 
              replace_program(BULLETIN_BOARD); 
      } 
       
       
