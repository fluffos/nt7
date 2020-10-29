inherit ROOM;
void create()
{
        set("short", "平原路");
        set("long",
"大道自西向东，地势渐平。路面铺着小石子，光脚走上去，觉得颇为\n"
"硌脚。道两旁的树木越来越少，骄阳似火，令人真想找个地方休息一下，\n"
"正好前面有家小酒馆。\n"
);
        set("exits", ([
  "east" : __DIR__"road1",
  "northwest" : __DIR__"inn",
]));
        set("outdoors", "llszhuang");
        setup();
}
