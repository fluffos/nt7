// book.c

inherit ITEM;

int is_book() { return 1; }

string extra_long()
{
        string str;
        
        str  = sprintf("\n物品属性 : 书本<秘籍>，下线%s丢失\n", 
                       (this_object()->query_autoload() || query("autoload")) ? "不" : "" );
        str += sprintf("记载内容 : %s\n", to_chinese(query("skill/name")));
        str += sprintf("经验要求 : %d\n", query("skill/exp_required"));
        str += sprintf("研习难度 : %d\n", query("skill/difficulty"));
        str += sprintf("研习要求 : %s %d 级\n", to_chinese(query("skill/name")), query("skill/min_skill"));
        str += sprintf("研习限制 : %d 级\n", query("skill/max_skill"));
        str += sprintf("精力消耗 : %d 点/次\n", query("skill/jing_cost"));
        // str += sprintf("研习方法 : 输入指令 du %s 研读。\n", query("id"));
        
        return str;
}
