// wudu.h

int permit_recruit(object ob)
{
        if( query("detach/五毒教", ob) || query("betrayer/五毒教", ob) )
        {
                command("say 你既然已经离教，就别再回来！");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 判师之徒，哼！小心我把你千刀万剐！");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "五毒教" )
        {
                command("say 你不是已经有了师傅么，还来干什么？做卧底么？");
                return 0;
        }

        if( query("family/master_name", ob) == "何铁手" )
        {
                command("sneer");
                command("say 既然你已经跟随了那个贱人，却又来找我作甚？");
                return 0;
        }

        return 1;
}
