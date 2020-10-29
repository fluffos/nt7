// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m睡袋[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "居家旅行必备之物。[2;37;0m
它是亚瑟王的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "mking");
        set("owner_name", "亚瑟王");
        set_temp("owner", "mking");
        set_temp("owner_name", "亚瑟王");
        ::setup();
}
