;;; Directory Local Variables
;;; For more information see (info "(emacs) Directory Variables")

;; ((nil . ((eval . (set (make-local-variable 'my-project-path)
;;                       (file-name-directory
;;                        (let ((d (dir-locals-find-file "./")))
;;                          (if (stringp d) d (car d))))))
;;          (cmake-ide-project-dir . my-project-path)
;;          (eval . (setq cmake-ide-build-dir (concat my-project-path "build")))
;;          ))
((nil . ((eval . (setq cmake-ide-build-dir
                       (concat (projectile-project-root) "/build"))
               ))))
