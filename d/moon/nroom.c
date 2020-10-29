// ken 1999.12.9

#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
	set("short", "内室");
	set("long", @LONG
这里只有柔和的灯光，华丽的陈设，精美的家具，一切布置的是
那么的恰如其分，旁边缕金香炉里散发出的阵阵幽香，另你忘却了
一切烦恼和疲劳。
LONG	);
        set("objects",([
			__DIR__"obj/xianglu" : 1,
       	]) );
	set("coor/x",-50);
	set("coor/y",1110);
	set("coor/z",40);
	setup();
}

void init()
{
add_action("do_turn","turn");
}

void close_path()
{
        if( !query("exits/north") ) return;
 message("vision","\n香炉又转了回来，暗门无声无息地合上了。\n",this_object() );
           delete("exits/north");
}

void closed_path()
{        
         if( !query("exits/east") ) return;
message("vision","\n香炉又转了回来，暗门无声无息地合上了。\n",this_object() );
           delete("exits/east");
}


int do_turn(string arg)
{    object me;
     me=this_player(); 
     if(!arg || arg=="")
        {
                write("你想向那个方向转动？\n");
                return 1;
        }
if( arg == "left")
    { if( (int)me->query("force_factor") >= 50 )
  {   message_vision("香炉吱吱转动，北墙上无声无息地裂开一扇暗门。\n",me);
	        if( !query("exits/north") ) 
               {
     		set("exits/north", __DIR__"mroom");
        	call_out("close_path", 5);
	        }
		return 1;	
       }
		else
		write("香炉纹丝不动。\n");
		return 1;
    } 
else
if( arg == "right")
    { if( (int)me->query("force_factor") >= 50 )
       {  message_vision("香炉吱吱转动，东墙上无声无息地裂开一扇暗门。\n",me);
	        if( !query("exits/east") ) 
               {
     		set("exits/east", __DIR__"wroom1");
        	call_out("closed_path", 5);
	        }
		return 1;	
        }
		else
		write("香炉纹丝不动。\n");
		return 1;
    } 
}
