// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m大无畏[2;37;0m[2;37;0m", ({"wuwei"}));        
        set("gender", "男性");                
        set("long", "$HIW$大无畏[2;37;0m
它是胡涂的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "huckr");
        set("owner_name", "胡涂");
        set_temp("owner", "huckr");
        set_temp("owner_name", "胡涂");
        ::setup();
}
