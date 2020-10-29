// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m瓦尔基里[2;37;0m[2;37;0m", ({"valkyr"}));        
        set("gender", "女性");                
        set("long", "$HIW$这是一位身披闪亮盔甲，骑着骏马在天空中飞行的少女战士。[2;37;0m
它是萤火之光的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "haniceme");
        set("owner_name", "萤火之光");
        set_temp("owner", "haniceme");
        set_temp("owner_name", "萤火之光");
        ::setup();
}
