#include <ansi.h>
#define QUESTDG_D(x)      ("/quest/questdg/quest/questdg" + x)

mapping query_questdg() 
{
        mapping questdg = ([]);

        if (random(25) == 10)
                questdg = QUESTDG_D("7find")->query_questdg();
        else if (random(2) == 1)
                questdg = QUESTDG_D("6find")->query_questdg();
        else
        questdg = QUESTDG_D("6kill")->query_questdg();
        if (questdg["type"] == "寻") 
        {
                if (random(5) == 3)
                {
                        questdg["type"] = "送";
                        questdg["name"] = "回执";
                }
        } 
        if (questdg["type"] == "杀") 
        {
                if (random(3) == 2)
                {
                        questdg["type"] = "擒";
                }
        } 
        return questdg;
}
