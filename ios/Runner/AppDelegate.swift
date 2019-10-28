import UIKit
import Flutter

@UIApplicationMain
@objc class AppDelegate: FlutterAppDelegate {
    
  override func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {
    
    let controller : FlutterViewController = window?.rootViewController as! FlutterViewController
    let scanChannel = FlutterMethodChannel(name: "scandit/scan", binaryMessenger: controller.binaryMessenger)
    
    scanChannel.setMethodCallHandler({
      [weak self] (call: FlutterMethodCall, result: @escaping FlutterResult) -> Void in
        self?.window?.rootViewController = nil
            
        let viewToPush = ScanViewController()
        
        let navigationController = UINavigationController(rootViewController: controller)
        
        self?.window = UIWindow(frame: UIScreen.main.bounds)
        self?.window?.makeKeyAndVisible()
        self?.window.rootViewController = navigationController
        navigationController.isNavigationBarHidden = true
        navigationController.pushViewController(viewToPush, animated: true)
    })
    
    GeneratedPluginRegistrant.register(with: self)
    return super.application(application, didFinishLaunchingWithOptions: launchOptions)
  }
}
