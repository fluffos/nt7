// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m凤仙[2;37;0m[2;37;0m", ({"xiaofxs"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是小凤仙的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xiaofx");
        set("owner_name", "小凤仙");
        set_temp("owner", "xiaofx");
        set_temp("owner_name", "小凤仙");
        ::setup();
}
