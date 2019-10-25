//
//  ScanViewController.swift
//  Runner
//
//  Created by Jordy Kingama on 25/10/2019.
//  Copyright © 2019 The Chromium Authors. All rights reserved.
//

import UIKit
import ScanditBarcodeCapture
import ScanditCaptureCore

class ScanViewController: UIViewController {
    
     
    private var camera: Camera?
    private var captureView: DataCaptureView!
    private var overlay: BarcodeCaptureOverlay!
    
    private let licenseKey = "ASZNzBM2DZY4IEiCpCQJw8gjCMd9Jv2IzFPJA8hCr1NDeW0VN2rR7rU7fbB5f7LFuVZ5PzBvZ/iPYam0zkWJCbhvNvYSciUR9m2vLkJPMxGzS+j+CEEUh1dJAo7GF5Jyjj8u+Xcf15FxRI3YBZpajOFWkFbDMyoNNvoAEdli7YvUBjKJIC4IH6Mb3wVhIfy7Ddk41Xw+YDGkZPCCcgxBfmweIbCsQy45yg9Zx7qtd2LPrYHaZVa6OhXchImXHZrEMoZ9etdnGc7XNoPgZDiaSTuw7FszzE4pfHRsJntzC8Sx7UHFeiBcLXFSndzG9l93e2xZqsxDUxEraIFzOHyPdaEITJ+w02HzD6gFjlhOysR06ZSflpEVy+OPPLYBcBGk8jTJTEIBupIsnYxlxYSnFba5klT4EhERNreER6Yb2ieovmP7/cTahwYcfBjKnaGF2W0ZKsMCiY4VpzXODl17t580r1Vpnq1SvgkJmOq7xN/KFktKieRgeA1lh9uiCdgEZ5fGfpqrBLFKi64g070+pzdhEe9+7sMh2u4ad2guhM2mkqeaqdPGB8CXit221AXf9t9UUuTo/T2ij1FnFyKQdzXdpdoAvhj7t5obnGi3B3M6Iz/I5Weh5Xy8+Mv3CNCUjIp+2v2cz824UWyT2iIK2m6k1L11C17YMUK77W/IHv1NwmE8jfDpN1FXSeN7mUtxJhehVcJmKf9FGtlvxlKl2vWNDmmGo2CJY/ag4AxoxeQgT5+6c/z0aNdT9tQMwsMgbG7vL6yDLMXMYHq0NMNSVwPRLYff9a1NAoCLczRUqkE+DO+E5HDLK4XI"
    
    lazy var settings: BarcodeCaptureSettings = {
        let captureSettings = BarcodeCaptureSettings()
        captureSettings.set(symbology: .code128, enabled: true)
        captureSettings.set(symbology: .code39, enabled: true)
        captureSettings.set(symbology: .qr, enabled: true)
        captureSettings.set(symbology: .ean8, enabled: true)
        captureSettings.set(symbology: .upce, enabled: true)
        captureSettings.set(symbology: .ean13UPCA, enabled: true)
        return captureSettings
    }()
    
    lazy var context: DataCaptureContext = {
        return DataCaptureContext(licenseKey: licenseKey)
    }()
    
    lazy var barcodeCapture: BarcodeCapture = {
        let barcodeCapture = BarcodeCapture(context: context, settings: settings)
        barcodeCapture.addListener(self)
        return barcodeCapture
    }()

    override func viewDidLoad() {
        super.viewDidLoad()
        setupRecognition()
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)

        // Switch camera on to start streaming frames. The camera is started asynchronously and will take some time to
        // completely turn on.
        barcodeCapture.isEnabled = true
        camera?.switch(toDesiredState: .on)
    }

    override func viewDidDisappear(_ animated: Bool) {
        super.viewDidDisappear(animated)

        // Switch camera off to stop streaming frames. The camera is stopped asynchronously and will take some time to
        // completely turn off. Until it is completely stopped, it is still possible to receive further results, hence
        // it's a good idea to first disable barcode capture as well.
        barcodeCapture.isEnabled = false
        camera?.switch(toDesiredState: .off)
    }
    
    func setupRecognition() {
        // Create data capture context using your license key.
        //scontext = DataCaptureContext.licensed

        // Use the world-facing (back) camera and set it as the frame source of the context. The camera is off by
        // default and must be turned on to start streaming frames to the data capture context for recognition.
        // See viewWillAppear and viewDidDisappear above.
        camera = Camera.default
        context.setFrameSource(camera, completionHandler: nil)

        // Use the recommended camera settings for the BarcodeCapture mode.
        let recommenededCameraSettings = BarcodeCapture.recommendedCameraSettings()
        camera?.apply(recommenededCameraSettings)

        // The barcode capturing process is configured through barcode capture settings
        // and are then applied to the barcode capture instance that manages barcode recognition.
        let settings = BarcodeCaptureSettings()

        // The settings instance initially has all types of barcodes (symbologies) disabled. For the purpose of this
        // sample we enable a very generous set of symbologies. In your own app ensure that you only enable the
        // symbologies that your app requires as every additional enabled symbology has an impact on processing times.
        settings.set(symbology: .ean13UPCA, enabled: true)
        settings.set(symbology: .ean8, enabled: true)
        settings.set(symbology: .upce, enabled: true)
        settings.set(symbology: .qr, enabled: true)
        settings.set(symbology: .dataMatrix, enabled: true)
        settings.set(symbology: .code39, enabled: true)
        settings.set(symbology: .code128, enabled: true)
        settings.set(symbology: .interleavedTwoOfFive, enabled: true)

        // Some linear/1d barcode symbologies allow you to encode variable-length data. By default, the Scandit
        // Data Capture SDK only scans barcodes in a certain length range. If your application requires scanning of one
        // of these symbologies, and the length is falling outside the default range, you may need to adjust the "active
        // symbol counts" for this symbology. This is shown in the following few lines of code for one of the
        // variable-length symbologies.
        let symbologySettings = settings.settings(for: .code39)
        symbologySettings.activeSymbolCounts = Set(7...20) as Set<NSNumber>

        // Create new barcode capture mode with the settings from above.
        barcodeCapture = BarcodeCapture(context: context, settings: settings)

        // Register self as a listener to get informed whenever a new barcode got recognized.
        barcodeCapture.addListener(self)

        // To visualize the on-going barcode capturing process on screen, setup a data capture view that renders the
        // camera preview. The view must be connected to the data capture context.
        captureView = DataCaptureView(for: context, frame: view.bounds)
        captureView.autoresizingMask = [.flexibleWidth, .flexibleHeight]
        view.addSubview(captureView)

        // Add a barcode capture overlay to the data capture view to render the location of captured barcodes on top of
        // the video preview. This is optional, but recommended for better visual feedback.
        overlay = BarcodeCaptureOverlay(barcodeCapture: barcodeCapture)
        overlay.viewfinder = RectangularViewfinder()
        captureView.addOverlay(overlay)
    }

    private func showResult(_ result: String, completion: @escaping () -> Void) {
        DispatchQueue.main.async {
            let alert = UIAlertController(title: result, message: nil, preferredStyle: .alert)
            alert.addAction(UIAlertAction(title: "OK", style: .default, handler: { _ in completion() }))
            self.present(alert, animated: true, completion: nil)
        }
    }

}


extension ScanViewController: BarcodeCaptureListener {
    
    func barcodeCapture(_ barcodeCapture: BarcodeCapture, didScanIn session: BarcodeCaptureSession, frameData: FrameData) {
        guard let barcode = session.newlyRecognizedBarcodes.first else {
            return
        }

        // Stop recognizing barcodes for as long as we are displaying the result. There won't be any new results until
        // the capture mode is enabled again. Note that disabling the capture mode does not stop the camera, the camera
        // continues to stream frames until it is turned off.
        barcodeCapture.isEnabled = false

        // If you are not disabling barcode capture here and want to continue scanning, consider setting the
        // codeDuplicateFilter when creating the barcode capture settings to around 500 or even -1 if you do not want
        // codes to be scanned more than once.
        // Get the human readable name of the symbology and assemble the result to be shown.
        let symbology = SymbologyDescription(symbology: barcode.symbology).readableName
        let result = "Scanned: \(barcode.data) (\(symbology))"

        showResult(result) { [weak self] in
            // Enable recognizing barcodes when the result is not shown anymore.
            self?.barcodeCapture.isEnabled = true
        }
    }
}
