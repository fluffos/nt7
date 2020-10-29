// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m苍井空[2;37;0m[2;37;0m", ({"cjk"}));        
        set("gender", "女性");                
        set("long", "东洋岛国漂洋过海而来的美女童颜巨乳风姿绰约人见人爱花见花开[2;37;0m
它是周不通的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "butong");
        set("owner_name", "周不通");
        set_temp("owner", "butong");
        set_temp("owner_name", "周不通");
        ::setup();
}
