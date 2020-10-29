// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m香君[2;37;0m[2;37;0m", ({"lixjs"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是李香君的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lixj");
        set("owner_name", "李香君");
        set_temp("owner", "lixj");
        set_temp("owner_name", "李香君");
        ::setup();
}
