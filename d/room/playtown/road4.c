// /d/playertown/road4.c 碎石小道
// Build 1999.12.10 bmw

inherit BUILD_ROOM;

void create()
{
        set("short","碎石小道");
        set("long",
"这儿是小村的中心大街，南面是一片竹林，风吹过的时候沙沙的声音煞是动听，左右\n"
"看了看，西面隐约可以看一栋金黄色闪闪发光的奇怪建筑物，而东面的不远处有一座小亭。\n"
);

        set("outdoors","playertown");
              set("recordable_room",1); 
        set("exits",([
                "west"        :        __DIR__"road3",
                "east"        :        __DIR__"road6",
        ]));
        
        setup();
        
        // replace_program(ROOM);
        
}