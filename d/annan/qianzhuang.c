inherit ROOM;


void create ()
{
  set ("short","安南钱庄");
  set ("long", @LONG
这里是安南的钱庄。这里的信誉很好，有很多人来这里存钱。老板
正在那里打着算盘，伙计在门前热情地招呼着客人。
LONG);

  set("exits", ([ 

 "south":__DIR__"dongjie2",
      ]));
 
  set("objects",([
          __DIR__"npc/wu":1,
          ]));
  
  set("valid_startroom", 1);
  setup();
 
}
