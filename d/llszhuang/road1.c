inherit ROOM;
void create()
{
        set("short", "山中小路");
        set("long",
"这里山色甚是凄凉，道路更本来已是苔藓土滑，崎岖难行到后来更是\n"
"乱山峥嵘，荒草没径。路边灌木丛生，每丛灌木上都长满了长达寸许的木\n"
"刺，木刺上还挂着各种颜色的布条。\n"
);
        set("exits", ([
  "west" : __DIR__"road2",
  "eastdown" : __DIR__"road",
]));
        set("outdoors", "llszhuang");
        setup();
}
