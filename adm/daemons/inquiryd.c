#include <ansi.h>

int parse_inquiry(object me, object ob, string topic)
{
        switch (topic)
        {
        case "name":
                message_vision(CYN "$N" CYN "向$n" CYN "问道：敢问" +
                               RANK_D->query_respect(ob) + "尊姓大"
                               "名？\n" NOR, me, ob);
                return 1;

        case "here":
                message_vision(CYN "$N" CYN "向$n" CYN "问道：这位" +
                               RANK_D->query_respect(ob) + "，" +
                               RANK_D->query_self(me) + "初到贵宝地"
                               "，不知这里有些什麽风土人情？\n" NOR,
                               me, ob);
                return 1;
        
        case "all":
                message_vision(CYN "$N" CYN "向$n" CYN "问道：这位" + 
                               RANK_D->query_respect(ob) + 
                               "，你都知道些什么事情呀？\n" NOR, 
                               me, ob);
                return 1;
                        
        case "clue":
        case "线索":
                message_vision(CYN "$N" CYN "向$n" CYN "打听道：" +
                               RANK_D->query_self(me) + "从旁人处得"
                               "知" + RANK_D->query_respect(ob) +
                               "有些线索，能否告知在下？\n" NOR, me, ob);
                return 1;

        case "rumor":
        case "rumors":
        case "消息":
                message_vision(CYN "$N" CYN "向$n" CYN "问道：这位" +
                               RANK_D->query_respect(ob) + "，不知"
                               "最近有没有听说什么消息？\n" NOR, me,
                               ob);
                return 1;

        case "marry":
                message_vision(CYN "$N眯着一双贼眼，不怀好意的向$n"+ 
                               CYN"问道：敢问这位"+RANK_D->query_respect(ob) +
                               "是否婚配？\n" NOR,me,ob);
                return 1;
        
        case "food":
                message_vision(CYN "$N可怜兮兮的向$n"+CYN"问道：“不知这位"+
                               RANK_D->query_respect(ob) +
                               "是否能给我点吃的, 在下已经三天没有进食了？”\n" NOR,
                               me,ob);
                return 1;
        
        case "water":
                message_vision(CYN "$N可怜兮兮的向$n"+CYN"问道：“不知这位"+
                               RANK_D->query_respect(ob) +
                               "是否能给我点喝的, 在下口渴得很？”\n" NOR,
                               me,ob);
                return 1;
        
        case "money":
                message_vision(CYN "$N双手抱拳向$n"+CYN"问道：“在下初来咋到，行走江湖缺了些盘缠,这位"+
                               RANK_D->query_respect(ob) +
                               "是否能施舍一二, 在下不甚感激？”\n" NOR,
                               me,ob);
                return 1;
                
        case "friend":
                message_vision(CYN "$N双手抱拳向$n"+CYN"说道：“四海之内皆兄弟也,这位"+
                               RANK_D->query_respect(ob) +
                               ",不知愿否与在下交个朋友”\n" NOR,
                               me,ob);
                return 1;
                
        default:
                return 0;
        }
}