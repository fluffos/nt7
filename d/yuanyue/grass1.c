// This program is a part of NITAN MudLIB

inherit ROOM; 
void create()
{
        set("short", "芳草坪"); 
        set("long", @LONG
这里是一块芳草坪，绿草茵茵，蝴蝶漫舞，花香扑鼻，让人感到
十分惬意。不禁令人就想一头躺倒上去，好好的去睡一觉，但这里偶
尔也会碰到菜花蛇。往西走是片小树林，北面则是一间卧室。
LONG );
        set("type","grassland");
        set("outdoors", "wansong");
        set("exits",([
                "east":__DIR__"grass2",
                "west":__DIR__"senling1",
                "north":__DIR__"woshi",
                "southeast":__DIR__"shibanlu4",
        ]) );
        
        set("objects",([
                "/clone/beast/caihuashe" : 1,
                __DIR__"obj/greengrass" : 1,
        ]) );
        set("coor/x",-600);
        set("coor/y",240);
        set("coor/z",80);
        setup();
        replace_program(ROOM);
}      
