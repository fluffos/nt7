inherit ROOM;
#include <ansi.h> 
void create()
{
        set("short", "龙潭");
        set("long",
"[1;31m这里就是龙潭，一只巨龙盘踞在这里，看见有人进来，发出\n"
"一声震天巨吼，然后便发起了攻击。听说它守护着精灵王留下来的宝藏。\n"
"有空的话，搜索(search)一下或许会有收获。\n"
);
        set("exits", ([ 
              // "south" : __DIR__"spirit6", 
           ]));
        set("objects", ([ 
             "/quest/tulong/npc/dragon" : 1,
          ]));
        set("book_count", 7);

        set("no_magic", 1);
        setup();
} 

void init()
{
  add_action ("do_search","search"); 
  add_action ("do_quit","train");}

int do_quit(string arg){
        write(query("name", this_player())+"，龙也是可以驯的么？！\n");
        return 1;
} 
int do_search (string arg)
{
  object who = this_player ();
  object where = this_object ();
  object book;

 if (query("book_count") < 1) 
  {
    message_vision ("$N四处搜索了一番，什么也没有找到。\n",who);  
    message_vision ("也许是被拿光了。\n",who);  
    return 1;
  }
        if (  present("night's diary", who) ) {
                return notify_fail("你都有这本书了，还要找什么。\n");
          }
 if( query_temp("mark/diary", who) )
   {
    message_vision ("$N四处搜索了一番，什么也没有找到。\n",who);  
    message_vision ("看样子是不能多拿的。\n",who);  
    return 1;
  }

  if (random(10))
  {
    message_vision ("$N四处搜索了一番，什么也没有找到。\n",who);  
  }
  else
  {
    book = new ("/quest/tulong/obj/diary");
    message_vision ("$N竟从枯树叶间找出一本"+YEL"夜辰日记"NOR+"！\n",who,book);
     set_temp("mark/diary", 1, who);
    book->move(who);  
message("channel:rumor",HIR"【精灵神界】某人："+query("name", this_player())+"找到夜辰日记啦。\n"NOR,users());
   addn("book_count", -1);
  }
  return 1;
}

void reset()
{
        ::reset();
        delete("exits/north");
}