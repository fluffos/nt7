inherit ROOM;

void create()
{
        set("short", "日本岛");
        set("long",@LONG
深切哀悼在9·18事变中牺牲的烈士，为我们的英雄报仇吧，杀入日本岛，冲啊~~
LONG);

	set("exits", ([
		"east"   : __DIR__"japan1",

	]));

   setup();

}

/*
void init() 
{ 
    object me;
      
    me = this_player(); 
      
    set("startroom", base_name(this_object()), me);
    me->save(); 
       
} 
*/
