// qingcheng.h

int permit_recruit(object ob)
{
        command("say 青城派暂不开放。");
        return 0;
        if( query("detach/青城派", ob) || 
            query("betrayer/青城派", ob) )
        {
                command("say 亏你还有脸回我青城派？给我滚开！");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 阁下不忠不信，我最痛恨你这种人了。");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "青城派" )
        {
                command("say 阁下既有了名师指点，还来我们青城派做什么？");
                return 0;
        }

        return 1;
}
