// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m焚焰金睛兽[2;37;0m[2;37;0m", ({"xieh"}));        
        set("gender", "男性");                
        set("long", "张牙舞爪、俯瞰众生[2;37;0m
它是伯赏昆瑜的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "scdyxieh");
        set("owner_name", "伯赏昆瑜");
        set_temp("owner", "scdyxieh");
        set_temp("owner_name", "伯赏昆瑜");
        ::setup();
}
