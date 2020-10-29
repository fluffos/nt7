inherit ROOM;

void create()
{
        set("short", "沼泽边缘");
        set("long", @LONG
这里乌云密布，天色极暗。再往前走就是武林中有名的死域 
－－火沼泽。那里不但荆棘密布，猛兽出没，还有能至人于死地 
在一瞬间随时喷射的毒火泉。这有原始森林入口(Forest door)。
LONG
        );
        set("item_desc", ([
                "door" : "从这个入口可以进入原始森林迷宫副本。(enter door)\n",
                "Forest door" : "从这个入口可以进入原始森林迷宫副本。(enter door)\n",
                "forest door" : "从这个入口可以进入原始森林迷宫副本。(enter door)\n",
        ]));

        set("exits",([
                "east" : __DIR__"yunnan1",
        ]));
        set("objects", ([ 
                "maze/forest/forest_door" : 1,
        ]));
	set("coor/x", -16770);
	set("coor/y", -7160);
	set("coor/z", 0);
	setup();
        // replace_program(ROOM);
}
