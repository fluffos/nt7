// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白帝[1;37m[2;37;0m[2;37;0m", ({"xin"}));        
        set("gender", "男性");                
        set("long", "杀气纵横[2;37;0m
它是谷神不死的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "weag");
        set("owner_name", "谷神不死");
        set_temp("owner", "weag");
        set_temp("owner_name", "谷神不死");
        ::setup();
}
