// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("三轮摩托[2;37;0m[2;37;0m", ({"hsleepbag"}));        
        set("gender", "男性");                
        set("long", "三轮摩托[2;37;0m
它是花田错的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xiaopeih");
        set("owner_name", "花田错");
        set_temp("owner", "xiaopeih");
        set_temp("owner_name", "花田错");
        ::setup();
}
