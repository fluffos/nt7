// This program is a part of NITAN MudLIB 
// redl 2015/10
// /clone/board/jinchuan_b.c 
#include <ansi.h>
        
inherit BULLETIN_BOARD; 
        
       void create() 
       { 
               set_name(YEL "金山" NOR, ({ "hill" , "golden hill" }) ); 
               set("location", "/u/redl/teleport/ailao"); 
               set("board_id", "jinchuan_b"); 
              set("long", "先行者可以在这上面刻点关于夺宝的心得体会。\n" ); 
              setup(); 
              set("capacity", 100); 
              replace_program(BULLETIN_BOARD); 
      } 
       
       
