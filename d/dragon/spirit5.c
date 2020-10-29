inherit ROOM; 
#include <ansi.h> 
void init();
int do_take(string arg);
int do_back(object me);

void create()
{ 
      set("short", "演武台");
      set("long",
"[1;32m这里看上去象是一个比武场，十丈见方的场地上整整齐齐地\n"
"铺着一圈彩色玛瑙石，架着香烟袅绕的四个巨大金银铜铁鼎，场地中间还\n"
"铺着软松的皮绒织锦毯。在场边有一个书架似的摆饰(shelf)，在它旁边\n"
"还有一张绢帛(note)。\n"
);
   set("exits",([
           "south" : __DIR__"xiuxishi",
]));
  set("objects",([
             "/quest/tulong/npc/shadow" : 1,
  ]));
  set("item_desc", ([
     "shelf" : "这是一个药架，里面放着一些金创药，似乎可以拿出来(take jinchuang)。\n", 
      "note" : "勇敢的人啊，如果你们的脚步到此为止，就回去凡间吧(back)。\n", 
  ]));
//  set("no_clean_up", 0);
  set("no_magic", 1);
        setup();
}

void init()
{
       // add_action("do_take", "take");
        add_action("do_back", "back");
      add_action("do_quit","hit");
      add_action("do_quit","kill");
      add_action("do_steal","steal");
}

int do_quit(string arg)
{
        write(query("name", this_player())+"，这里只能fight！\n");
        return 1;
}

int do_steal(string arg)
{
        write(query("name", this_player())+"，不要为此不才之事！\n");
        return 1;
}
int do_take(string arg)
{      
        object me=this_player();
        object ob;
        if(!arg || arg!="jinchuang")
          return notify_fail("你要拿什么？\n");
        if( !query("fighter", me) )
          return notify_fail("你还没比武就想拿药？\n"); 
       ob = new ("/clone/misc/jinchuang");   
       ob->move(me); 
  message_vision ("$N从台上拿起$n。\n",me,ob); 
        return 1;  
}

int do_back(object me)
{
        me=this_player();
        message_vision(HIC"$N的身影消失在一阵光芒中。\n"NOR,me); 
        set("fighter", 0, me);
        set_temp("m_success/初级", 0, me);
        set_temp("m_success/幻影", 0, me);
        set_temp("m_success/孽龙", 0, me);
        me->move("/d/city/wumiao");
        return 1;
}

/*
int valid_leave(string dir)
{
              if((present("jinchuang yao", this_player())))
            return notify_fail("请不要带走这里的东西。\n"); 
        if((present("budai", this_player())))
            return notify_fail("请放下布袋，这里的东西不能带出去，谢谢。\n"); 
    return ::valid_leave();

 }

*/