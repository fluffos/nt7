// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("蓝蓝[2;37;0m[2;37;0m", ({"lucas"}));        
        set("gender", "男性");                
        set("long", "小狗狗[2;37;0m
它是李子衿的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lyuee");
        set("owner_name", "李子衿");
        set_temp("owner", "lyuee");
        set_temp("owner_name", "李子衿");
        ::setup();
}
