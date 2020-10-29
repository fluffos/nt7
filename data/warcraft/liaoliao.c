// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("保时捷的轿跑[2;37;0m[2;37;0m", ({"panamera"}));        
        set("gender", "女性");                
        set("long", "保时捷轿跑[2;37;0m
它是聊啥的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "liaoliao");
        set("owner_name", "聊啥");
        set_temp("owner", "liaoliao");
        set_temp("owner_name", "聊啥");
        ::setup();
}
