// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "碧波池");
        set("long", @LONG
绕过如同石屏风一般的涵碧峰，是一汪晶莹剔透，碧玉般的池水。池
底有两眼活泉，一为寒泉，一为温泉，所以池水冬暖夏凉，四季不涸，且
水质特佳，不亚于天下任何名泉。池养鱼鳖，大多是罕见异种，其中五色
锦鲤嘻游嘬花，池中大鼋寿龄已达五百余岁。更传说池中有可克百毒的“
金娃娃”出现。北面隐隐约约有一座精舍，东面靠近池中心处有一块奇形
大石。
LONG );
         set("exits", ([
                "southwest" : __DIR__"hanbi",
                "east"      : __DIR__"tingyu",
                "north"     : __DIR__"jingshe",
        ]));

        set("outdoors", "taohua");

        set("coor/x", 8990);
        set("coor/y", -2960);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}