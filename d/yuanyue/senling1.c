inherit ROOM;
void create()
{
        set("short", "松林"); 
        set("long", @LONG
这里是圆月山庄后园一片密密的松木林，四周一片寂静。松针落
的遍地都是，几乎把整个小路铺成了条软软的松毯，不知名的野兔偷
偷逃过，小路旁就是条静静流淌的小溪，溪水上漂浮着松针黄叶，荡
开枝叶，依稀可看到溪水碧绿如镜，清澈见底。
LONG );
        set("outdoors", "wansong");
        set("type","forest");
        set("exits",([
                "east":__DIR__"grass1",
                "northwest":__DIR__"senling2",
        ]) );
        
        set("objects", ([
                CLASS_D("mojiao/fuhongxue") : 1,
        ]));
        set("coor/x",-610);
        set("coor/y",240);
        set("coor/z",80);
        setup();
        replace_program(ROOM);
}   
