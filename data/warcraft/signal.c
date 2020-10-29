// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("傅立叶[2;37;0m[2;37;0m", ({"fourier"}));        
        set("gender", "男性");                
        set("long", "一只朱雀[2;37;0m
它是陈雪的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "signal");
        set("owner_name", "陈雪");
        set_temp("owner", "signal");
        set_temp("owner_name", "陈雪");
        ::setup();
}
