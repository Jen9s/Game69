#include "Solder.h"

void FightFirstAttack_(Solder &first, Solder &second) {//Типа шаблон драки

    while (first.armor > 0 && second.armor > 0) {
        first.armor -= second.damage * 1.5;
        second.armor -= first.damage * 0.8;
    }

    first.healthy += first.armor;
    second.healthy += second.armor;

    while (first.healthy > 0 && second.healthy > 0) {
        first.healthy -= second.damage * 1.5;
        if (first.healthy <= 0) {
            std::cout << "Second win!";
            second.armor = 30;
            return;
        }
        second.healthy -= first.damage * 0.8;
        if (second.healthy <= 0) {
            std::cout << "First win!";
            first.armor = 30;
            return;
        }
    }

}

void AttackCastle(Hero &hero, Castle &castle) { //Старая функция  атаки замка героем
    int ArmyHeroSize = hero.HeroArmy.Army_.size();
    int AllHeroArmor = hero.armor + ArmyHeroSize * hero.HeroArmy.armor;
    int AllHeroHealthy = hero.healthy;
    for (int i = 0; i < ArmyHeroSize; i++) {
        AllHeroHealthy += hero.HeroArmy.Army_[i].healthy;
    }
    int AllHeroDamage =
            hero.damage * hero.AttackFactor + hero.HeroArmy.damage * hero.HeroArmy.AttackFactor * ArmyHeroSize;

    int ArmyCastleSize = castle.CastleArmy.Army_.size();
    int AllCastleArmor = ArmyCastleSize * hero.armor;
    int AllCastleHealthy = castle.CastleArmy.healthy * ArmyCastleSize;
    int AllCastleDamage = castle.CastleArmy.damage * castle.CastleArmy.AttackFactor * ArmyCastleSize;

    while (AllHeroArmor > 0 && AllCastleArmor > 0) {
        AllHeroArmor -= AllCastleDamage * 1.5;
        AllCastleArmor -= AllHeroDamage * 0.8;
    }

    AllHeroHealthy += AllHeroArmor;
    AllCastleHealthy += AllCastleArmor;

    while (AllHeroHealthy > 0 && AllCastleHealthy > 0) {
        AllHeroHealthy -= AllCastleDamage * 1.5;
        if (ArmyHeroSize > 0) {
            while ((ArmyHeroSize - 1) * hero.HeroArmy.healthy + hero.healthy >= AllHeroHealthy) {
                ArmyHeroSize--;
                AllHeroDamage = hero.damage * hero.AttackFactor +
                                hero.HeroArmy.damage * hero.HeroArmy.AttackFactor * ArmyHeroSize;
            }
        }
        if (AllHeroHealthy <= 0) {
            std::cout << " -_- ";
            hero.healthy = 0;
            hero.HeroArmy.Army_ = std::vector<Solder>{};
            return;
        }

        AllCastleHealthy -= AllHeroDamage * 0.8;
        while ((ArmyCastleSize - 1) * castle.CastleArmy.healthy > AllCastleHealthy) {
            ArmyCastleSize--;
            hero.KillCounter++;
            hero.HeroArmy.KillCounter++;
            hero.ChangeCounter();
            hero.HeroArmy.ChangeCounter();
            AllCastleDamage = castle.CastleArmy.damage * castle.CastleArmy.AttackFactor * ArmyCastleSize;
        }
        if (AllCastleHealthy <= 0) {
            if (AllHeroHealthy <= 200) {
                hero.healthy = AllHeroHealthy;
                hero.HeroArmy.Army_ = std::vector<Solder>{};
                for (int i = 0; i < castle.ValueRebuildingArmy; i++) {
                    Solder tmp;
                    hero.HeroArmy.Army_.push_back(tmp);
                }
            } else {
                AllHeroHealthy -= hero.healthy;

                int j = 0;
                std::vector<Solder> tmpArmy;
                while (AllHeroHealthy >= 80){
                    AllHeroHealthy -= hero.HeroArmy.Army_[j].healthy;
                    if(AllHeroHealthy  >= 80)
                        tmpArmy.push_back(hero.HeroArmy.Army_[j]);
                    j++;
                }
                for (int i = 0; i < castle.ValueRebuildingArmy; i++) {
                    Solder tmp;
                    tmpArmy.push_back(tmp);
                }
                j--;
                if(AllHeroHealthy != 0 ) {
                    if (AllHeroHealthy > 0) {
                        tmpArmy.push_back(hero.HeroArmy.Army_[j]);
                        tmpArmy[tmpArmy.size() - 1].healthy = AllHeroHealthy;
                    } else {
                        AllHeroHealthy += hero.HeroArmy.Army_[j].healthy;
                        tmpArmy.push_back(hero.HeroArmy.Army_[j]);
                        tmpArmy[tmpArmy.size() - 1].healthy = AllHeroHealthy;
                    }
                }

                hero.HeroArmy.Army_ = tmpArmy;
                /*AllHeroHealthy -= (ArmyHeroSize - 1) * hero.HeroArmy.healthy;
                hero.HeroArmy.Army_ = std::vector<Solder>{};
                for (int i = 0; i < ArmyHeroSize - 1 + castle.ValueRebuildingArmy; i++) {
                    Solder tmp;
                    hero.HeroArmy.Army_.push_back(tmp);
                }
                if (AllHeroHealthy != 0) {
                    Solder tmp;
                    tmp.healthy = AllHeroHealthy;
                    hero.HeroArmy.Army_.push_back(tmp);
                }*/

            }
            castle.CastleArmy.Army_ = std::vector<Solder>{};
            hero.CastlesCounter++;
            castle.WhoseCastle = "My! How can I not remember! ";
            return;
        }
    }
}

void DeleteElementVector(std::vector<Solder>& VecSolder,int element ){
    std::vector<Solder> VecSolderCopy;
    for(int i = 0 ;i < VecSolder.size() - 1;i++){
        if(i != element){
            VecSolderCopy.push_back(VecSolder[i]);
        }
    }
    VecSolder = VecSolderCopy;
}

void Attack(Castle &castle,Hero& hero){

    while (hero.healthy > 0 ){
        for(int i = 0; i < castle.CastleArmy.Army_.size(); i++ ){
            int j = 0;
            if(!hero.HeroArmy.Army_.empty()) {
                int k =  hero.HeroArmy.Army_.size() - 1;
                if(k != 0)
                    j = rand() % k;
                hero.HeroArmy.Army_[j].armor -= castle.CastleArmy.Army_[i].damage;
                if (hero.HeroArmy.Army_[j].armor < 0) {
                    hero.HeroArmy.Army_[j].healthy += hero.HeroArmy.Army_[j].armor;
                    if (hero.HeroArmy.Army_[j].healthy < 0) {
                        DeleteElementVector(hero.HeroArmy.Army_, j);
                    }
                    hero.HeroArmy.Army_[j].armor = 0;
                }
            }
            else{
                hero.armor -= castle.CastleArmy.Army_[i].damage;
                if(hero.armor < 0){
                    hero.healthy += hero.armor;
                    if(hero.healthy < 0){
                        hero.healthy = 0;
                        hero.armor = 0;
                        return;
                    }
                    hero.armor = 0;
                }
            }
        }

        for(int i = 0; i < hero.HeroArmy.Army_.size(); i++ ){
                int k =  castle.CastleArmy.Army_.size() -1;
                int j = 0;
                if(k != 0)
                    j = rand() % k;
                castle.CastleArmy.Army_[j].armor -= hero.HeroArmy.Army_[i].damage;
                if (castle.CastleArmy.Army_[j].armor < 0) {
                    castle.CastleArmy.Army_[j].healthy += castle.CastleArmy.Army_[j].armor;
                    if (castle.CastleArmy.Army_[j].healthy < 0) {
                        DeleteElementVector(castle.CastleArmy.Army_, j);
                        hero.KillCounter++;
                        hero.ChangeCounter();
                        if(castle.CastleArmy.Army_.empty()){
                            for(int e = 0; e < hero.HeroArmy.Army_.size(); e++ )
                                hero.HeroArmy.Army_[e].armor = 40;
                            return;
                        }
                    }
                    castle.CastleArmy.Army_[j].armor = 0;
                }
        }
    }

}

void MyGame() {
    int counter = 0;
    Hero MainCharacter;
    Castle MainCharacterCastle;
    Hero GeneralGafs("General Gafs");
    Castle First_C(2, 3, "Minsk");
    Castle Second_C(3, 3, "Kiev");
    Castle Third_C(4, 3, "Moscow");
    std::cout << "  Hello " << MainCharacter.name << " ! You have a very important mission to kill the GeneralGafs, "
              << std::endl
              << " who is attacking your castles and robbing them. " << std::endl
              << " First you need to capture 3 of his castles(Minsk,Kiev,Moscow) to make him attackable. " << std::endl
              << " Of course, your army will help you! Which can improve just like you. " << std::endl
              << " To lead your army as well as get useful information, " << std::endl
              << " use the commands: attack, duel, scout, info,stop(if you want to exit the game) ." << std::endl
              << " Good game ! And may the force be with you!" << std::endl << std::endl;
    for (;;) {
        std::string Action;
        std::cout << "Enter action : ";
        std::cin >> Action;
        if (Action != "attack" && Action != "scout" && Action != "duel" && Action != "info" && Action != "stop") {
            std::cout << "You can't do it." << std::endl;
            goto exit;
        }

        if (Action == "info") {
            std::cout << "Your level is " << MainCharacter.LevelCounter << ". Your attack factor is "
                      << MainCharacter.AttackFactor
                      << ". " << std::endl << " Your army level is " << MainCharacter.HeroArmy.LevelCounter
                      << ". Your attack factor army is " << MainCharacter.HeroArmy.AttackFactor;
            if (MainCharacter.HeroArmy.Army_[MainCharacter.HeroArmy.Army_.size() - 1].healthy ==
                MainCharacter.HeroArmy.healthy) {
                std::cout << ". " << std::endl << " Your army size is " << MainCharacter.HeroArmy.Army_.size()
                          << ". Your army is full !" << std::endl;
            } else {
                std::cout << ". " << std::endl << " Your army size is " << MainCharacter.HeroArmy.Army_.size()
                          << ". Your army is not  full !" << " Your last squad  has "
                          << MainCharacter.HeroArmy.Army_[MainCharacter.HeroArmy.Army_.size() - 1].healthy << " hp."
                          << std::endl;
            }
        }
        if (Action == "duel") {
            if (First_C.WhoseCastle == "My! How can I not remember! " &&
                Second_C.WhoseCastle == "My! How can I not remember! " &&
                Third_C.WhoseCastle == "My! How can I not remember! ") {
                std::cout << "Which hero do you want to attack ?" << std::endl;
                std::cin >> Action;
                if (Action == "GeneralGafs") {
                    MainCharacter.Duel(GeneralGafs);
                } else {
                    std::cout << "Unknown character." << std::endl;
                    goto exit;
                }
            } else {
                std::cout << " You can't attack General Gafs. Firstly you should capture castles! " << std::endl;
                goto exit;
            }
        }
        if (Action == "attack") {
            std::cout << "What castle do you want to attack ? " << std::endl;
            std::cin >> Action;
            if (Action == First_C.name || Action == Second_C.name || Action == Third_C.name) {
                if (Action == First_C.name) {
                    if (First_C.WhoseCastle == "My! How can I not remember! ") {
                        std::cout << " Castle is mine! How can I not remember! " << std::endl;
                        goto exit;
                    } else {
                        int tmp_ = MainCharacter.HeroArmy.Army_.size();
                        Attack(First_C,MainCharacter);
                        First_C.WhoseCastle = "My! How can I not remember! ";
                        if (MainCharacter.healthy > 0) {
                            tmp_ += First_C.ValueRebuildingArmy - MainCharacter.HeroArmy.Army_.size();
                            std::cout << " You lost "
                                      << tmp_
                                      << " squads while capturing the castle.";
                            std::cout << " But you get " << First_C.ValueRebuildingArmy << " squads." << std::endl;
                        }
                    }
                }
                if (Action == Second_C.name) {
                    if (Second_C.WhoseCastle == "My! How can I not remember! ") {
                        std::cout << " Castle is mine! How can I not remember! " << std::endl;
                        goto exit;
                    } else {
                        int tmp_ = MainCharacter.HeroArmy.Army_.size();
                        Attack(Second_C ,MainCharacter);
                        Second_C.WhoseCastle = "My! How can I not remember! ";
                        if (MainCharacter.healthy > 0) {
                            tmp_ += -MainCharacter.HeroArmy.Army_.size() + Second_C.ValueRebuildingArmy;
                            std::cout << " You lost "
                                      << tmp_
                                      << " squads while capturing the castle.";
                            std::cout << " But you get " << Second_C.ValueRebuildingArmy << " squads." << std::endl;
                        }
                    }
                }
                if (Action == Third_C.name) {
                    if (Third_C.WhoseCastle == "My! How can I not remember! ") {
                        std::cout << " Castle is mine! How can I not remember! " << std::endl;
                        goto exit;
                    } else {
                        int tmp_ = MainCharacter.HeroArmy.Army_.size();
                        Attack(Third_C,MainCharacter);
                        Third_C.WhoseCastle = "My! How can I not remember! ";
                        if (MainCharacter.healthy > 0) {
                            tmp_ += -MainCharacter.HeroArmy.Army_.size() + Second_C.ValueRebuildingArmy;
                            std::cout << " You lost "
                                      << tmp_
                                      << " squads while capturing the castle.";
                            std::cout << " But you get " << Third_C.ValueRebuildingArmy << " squads." << std::endl;
                        }
                    }
                }
            } else {
                std::cout << " You can't attack this. " << std::endl;
                goto exit;
            }

        }
        if (Action == "scout") {
            std::cout << "Do you want to scout some castle or enemy hero? " << std::endl;
            std::cin >> Action;
            if (Action == "castle" || Action == "hero") {
                if (Action == "hero") {
                    std::cout << " Sorry, this add-on is worth buying first! " << std::endl
                              << " Throw money here! 5578 8433 7057 1899 " << std::endl;
                } else {
                    std::cout << " Which castle do you want to scout? " << std::endl;
                    std::cin >> Action;
                    if (Action == First_C.name || Action == Second_C.name || Action == Third_C.name) {
                        if (Action == First_C.name) {
                            if (First_C.WhoseCastle == "My! How can I not remember! ")
                                std::cout << " This castle is yours! How can you not remember!" << std::endl;
                            else {
                                std::cout << " Castle is not mine. It have " << First_C.CastleArmy.Army_.size()
                                          << " squads." << std::endl;
                            }
                        }
                        if (Action == Second_C.name) {
                            if (Second_C.WhoseCastle == "My! How can I not remember! ")
                                std::cout << " This castle is yours! How can you not remember!" << std::endl;
                            else {
                                std::cout << " Castle is not mine. It have " << Second_C.CastleArmy.Army_.size()
                                          << " squads." << std::endl;
                            }
                        }
                        if (Action == Third_C.name) {
                            if (Third_C.WhoseCastle == "My! How can I not remember! ")
                                std::cout << " This castle is yours! How can you not remember!" << std::endl;
                            else {
                                std::cout << " Castle is not mine. It have " << Third_C.CastleArmy.Army_.size()
                                          << " squads." << std::endl;
                            }
                        }
                    } else {
                        std::cout << " Sorry, I don't know this castle." << std::endl;
                        goto exit;
                    }
                }
            } else {
                std::cout << " You can't scout this. " << std::endl;
                goto exit;
            }
        }

        if (MainCharacter.healthy <= 0) {
            std::cout << " You lose !";
            return;
        }
        if (
                First_C.WhoseCastle == "My! How can I not remember! "
                && Second_C.WhoseCastle == "My! How can I not remember! "
                && Third_C.WhoseCastle == "My! How can I not remember! "
                && counter == 0
            ) {
            counter++;
            std::cout << "You can attack General Gafs !" << std::endl;
        }
        if (GeneralGafs.healthy <= 0) {
            std::cout << " ◄ You win!‼!‼! ☺☺☺ ♫♫ My congratulations$ !‼!‼!‼! ►";//Жаль что смайлики  не выводиться (
            return;
        }
        exit:
        if (Action == "stop") {
            return;
        }

    }
}

int main() {
    MyGame();
    /*Castle First_C(2, 3, "Minsk");
    Castle Second_C(3, 5, "Kiev");
    Castle Third_C(4, 7, "Moscow");
    Hero hero;
    AttackCastle(hero,First_C);
    Attack(First_C,hero);
    Attack(Second_C,hero);*/
/*    AttackCastle(hero,Second_C);

    AttackCastle(hero,Third_C);*/
    return 0;
}
