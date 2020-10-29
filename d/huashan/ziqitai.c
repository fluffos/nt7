inherit BUILD_ROOM;

void create()
{
        set("short", "紫气台");
        set("long", @LONG
紫气台终年云遮雾掩，迷蒙不见天日，更为怪异的是：每逢下雨
天，山谷之中就隐隐有紫气出现。极目四望，风景如画。在这里隐居
相必非常惬意。
LONG );
        set("outdoors", "huashan");
        set("exits",([ /* sizeof() == 1 */
            "eastdown": __DIR__"chaopath2",
            "up": "/d/reborn/jitan2",
        ]));
        set("max_room", 3);
        setup();
}
