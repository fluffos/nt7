// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m玉峰[2;37;0m[2;37;0m", ({"gumus"}));        
        set("gender", "女性");                
        set("long", "哈哈[2;37;0m
它是沽沐的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "gumu");
        set("owner_name", "沽沐");
        set_temp("owner", "gumu");
        set_temp("owner_name", "沽沐");
        ::setup();
}
