// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("葫芦猫[2;37;0m[2;37;0m", ({"brilla"}));        
        set("gender", "女性");                
        set("long", "一只葫芦猫[2;37;0m
它是中文姓氏的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "datura");
        set("owner_name", "中文姓氏");
        set_temp("owner", "datura");
        set_temp("owner_name", "中文姓氏");
        ::setup();
}
