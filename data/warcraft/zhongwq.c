// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("王其[2;37;0m[2;37;0m", ({"wwqq"}));        
        set("gender", "男性");                
        set("long", "王其[2;37;0m
它是钟王其的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zhongwq");
        set("owner_name", "钟王其");
        set_temp("owner", "zhongwq");
        set_temp("owner_name", "钟王其");
        ::setup();
}
