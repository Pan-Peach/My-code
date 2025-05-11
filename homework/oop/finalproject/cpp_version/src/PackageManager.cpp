bool PackageManager::addPackage(std::shared_ptr<Package> package) {
    // 插入到链表
    incomingPackages.push_front(package);
    
    // 在哈希表中记录位置
    packageMap[package->getId()] = incomingPackages.begin();
    
    return true;
}
